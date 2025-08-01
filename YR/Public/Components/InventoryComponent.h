// Copyright © 2025 yizhixiachan

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ESData/DummyData.h"
#include "InventoryComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class YR_API UInventoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    void InitializeDataTables(
        UDataTable* InWeaponTable,
        UDataTable* InGearTable,
        UDataTable* InConsumableItemTable,
        UDataTable* InQuestItemTable
    );

    void InitializeInventoryData(
        TMap<FItemUID, int32> InAllItemMap,
        TMap<int32, FWeaponInstance> InAllWeaponMap,
        TMap<int32, FGearInstance> InAllGearMap,
        int32 InInventorySize,
        int32 InMoney,
        int32 InNextWeaponID,
        int32 InNextGearID
    );

public:
    //~ 开始背包接口
    bool AddOrBuyItem(FItemUID ItemUID, int32 Count = 1, bool IsBuy = false);
    bool RemoveOrSaleItem(FItemUID ItemUID, int32 Count = 1, bool IsSale = false);
    int32 GetPriceByItemUID(FItemUID ItemUID, bool IsDirect) const;
    bool ItemTrade(FItemUID ItemUID, int32 Count, bool IsBuy);
    void GenerateAndAddWeapon(TMap<EWeaponAttribute, FRangeValue> WeaponAttribute, int32 OID);
    void GenerateAndAddGear(TMap<EGearAttribute, FRangeValue> GearAttribute, int32 OID);
    void Equip(FItemUID ItemUID, TMap<int32, FDummyAttributes>& AllCharAttrMap, int32 CurCharIndex);
    void Unequip(FItemUID ItemUID, TMap<int32, FDummyAttributes>& AllCharAttrMap, int32 CurCharIndex);
    void UseConsumable(FItemUID ItemUID, TMap<int32, FDummyAttributes>& AllCharAttrMap, int32 CurCharIndex, int32 Count = 1);
    TMap<FItemUID, int32> GetClassifiedItemMap(EItemType ItemType) const;

    //~ 开始查表函数模板
    template<typename T>
    T* GetItemRowByItemUID(FItemUID ItemUID) const
    {
        static const FString ContextString("GetItemRowByItemUID");

        /**延迟求值的静态断言 */ 
        static_assert(!std::is_same_v<T, T> && false, "Unsupported TableRow type");

        return nullptr;
    }
    template<>
    FWeaponRow* GetItemRowByItemUID<FWeaponRow>(FItemUID ItemUID) const
    {
        return GetItemRowWithMapping<FWeaponRow>(ItemUID, WeaponTable, AllWeaponMap);
    }
    template<>
    FGearRow* GetItemRowByItemUID<FGearRow>(FItemUID ItemUID) const
    {
        return GetItemRowWithMapping<FGearRow>(ItemUID, GearTable, AllGearMap);
    }
    template<>
    FConsumableItemRow* GetItemRowByItemUID<FConsumableItemRow>(FItemUID ItemUID) const
    {
        return GetItemRowDirect<FConsumableItemRow>(ItemUID, ConsumableItemTable);
    }
    template<>
    FQuestItemRow* GetItemRowByItemUID<FQuestItemRow>(FItemUID ItemUID) const
    {
        return GetItemRowDirect<FQuestItemRow>(ItemUID, QuestItemTable);
    }

    FWeaponRow* GetWeaponRowByItemUID(FItemUID ItemUID) const
    {
        return GetItemRowDirect<FWeaponRow>(ItemUID, WeaponTable);
    }

    FGearRow* GetGearRowByItemUID(FItemUID ItemUID) const
    {
        return GetItemRowDirect<FGearRow>(ItemUID, GearTable);
    }

    //~ 结束查表函数模板

    TMap<FItemUID, int32> GetAllItemMap() const { return AllItemMap; }

    TMap<int32, FWeaponInstance> GetAllWeaponMap() const{ return AllWeaponMap; }
    TMap<int32, FGearInstance> GetAllGearMap() const{ return AllGearMap; }
    int32 GetInventorySize() const{ return InventorySize; }
    void SetInventorySize(int32 NewSize) { InventorySize = NewSize; }
    int32 GetMoney() const{ return Money; }
    void SetMoney(int32 NewMoney) { Money = NewMoney; }
    int32 GetNextWeaponID() const{ return NextWeaponID; }
    int32 GetNextGearID() const{ return NextGearID; }
    //~ 结束背包接口

private:
    //~ 开始Utility Functions
    template<typename RowType, typename MapType>
    RowType* GetItemRowWithMapping(FItemUID ItemUID, UDataTable* Table, const MapType& ItemMap) const
    {
        static const FString ContextString("GetItemRowByItemUID");
        const auto* FoundItem = ItemMap.Find(ItemUID.ID);
        FName RowName = FName(*FString::FromInt(FoundItem->OID));
        RowType* Row = Table->FindRow<RowType>(RowName, ContextString);
        return Row;
    }
    template<typename RowType>
    RowType* GetItemRowDirect(FItemUID ItemUID, UDataTable* Table) const
    {
        static const FString ContextString("GetItemRowByItemUID");
        FName RowName = FName(*FString::FromInt(ItemUID.ID));
        RowType* Row = Table->FindRow<RowType>(RowName, ContextString);
        return Row;
    }
    //~ 结束Utility Functions
private:
    //~ 开始初始化数据
    /**数据表 */
    UPROPERTY()
    UDataTable* WeaponTable = nullptr;
    UPROPERTY()
    UDataTable* GearTable = nullptr;
    UPROPERTY()
    UDataTable* ConsumableItemTable = nullptr;
    UPROPERTY()
    UDataTable* QuestItemTable = nullptr;

    /**所有物品数据 */
    TMap<FItemUID, int32> AllItemMap;

    /**所有拥有的装备实例数据 */
    TMap<int32, FWeaponInstance> AllWeaponMap;
    TMap<int32, FGearInstance> AllGearMap;

    /**背包容量 */
    int32 InventorySize = 100;

    /**拥有的钱数 */
    int32 Money = 0;

    /**下一件装备实例的ID */
    int32 NextWeaponID = 1;
    int32 NextGearID = 1;
    //~ 结束初始化数据
};
