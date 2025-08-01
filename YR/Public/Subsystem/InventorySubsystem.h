// Copyright © 2025 yizhixiachan

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ESData/DummyData.h"
#include "InventorySubsystem.generated.h"

class UInventoryComponent;

UCLASS()
class YR_API UInventorySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const;
	virtual void Initialize(FSubsystemCollectionBase& Collection);
	virtual void Deinitialize();

public:
	//~ 开始暴露给蓝图的接口
	UFUNCTION(BlueprintCallable, Category = "Inventory|Items")
	const UInventoryComponent* GetInventory() const;
	UFUNCTION(BlueprintCallable, Category = "Inventory|Items")
	void InitializeDataTables(
		UDataTable* InWeaponTable,
		UDataTable* InGearTable,
		UDataTable* InConsumableItemTable,
		UDataTable* InQuestItemTable
	);
	UFUNCTION(BlueprintCallable, Category = "Inventory|Items")
	void InitializeInventoryData(
		TMap<FItemUID, int32> InAllItemMap,
		TMap<int32, FWeaponInstance> InAllWeaponMap,
		TMap<int32, FGearInstance> InAllGearMap,
		int32 InInventorySize,
		int32 InMoney,
		int32 InNextWeaponID,
		int32 InNextGearID
	);
	UFUNCTION(BlueprintCallable, Category = "Inventory|Items")
	bool AddOrBuyItem(FItemUID ItemUID, int32 Count = 1, bool IsBuy = false);
	UFUNCTION(BlueprintCallable, Category = "Inventory|Items")
	bool RemoveOrSaleItem(FItemUID ItemUID, int32 Count = 1, bool IsSale = false);
	UFUNCTION(BlueprintCallable, Category = "Inventory|Items")
	bool ItemTrade(FItemUID ItemUID, int32 Count, bool IsBuy);
	UFUNCTION(BlueprintCallable, Category = "Inventory|RowData")
	int32 GetPriceByItemUID(FItemUID ItemUID, bool IsDirect) const;
	UFUNCTION(BlueprintCallable, Category = "Inventory|RowData")
	FItemTableRow GetItemRow(FItemUID ItemUID, bool IsDirect) const;
	UFUNCTION(BlueprintCallable, Category = "Inventory|RowData")
	FWeaponRow GetWeaponRowByItemUID(FItemUID ItemUID) const;
	UFUNCTION(BlueprintCallable, Category = "Inventory|RowData")
	FGearRow GetGearRowByItemUID(FItemUID ItemUID) const;

	UFUNCTION(BlueprintCallable, Category = "Inventory|Items")
	void GenerateAndAddWeapon(TMap<EWeaponAttribute, FRangeValue> WeaponAttribute, int32 OID);
	UFUNCTION(BlueprintCallable, Category = "Inventory|Items")
	void GenerateAndAddGear(TMap<EGearAttribute, FRangeValue> GearAttribute, int32 OID);
	UFUNCTION(BlueprintCallable, Category = "Inventory|Items")
	void Equip(FItemUID ItemUID);
	UFUNCTION(BlueprintCallable, Category = "Inventory|Items")
	void Unequip(FItemUID ItemUID);
	UFUNCTION(BlueprintCallable, Category = "Inventory|Items")
	void UseConsumable(FItemUID ItemUID, int32 Count = 1);
	UFUNCTION(BlueprintCallable, Category = "Inventory|Items")
	TMap<FItemUID, int32> GetClassifiedItemMap(EItemType ItemType) const;
	UFUNCTION(BlueprintCallable, Category = "Inventory|Items")
	TMap<FItemUID, int32> GetAllItemMap() const;
	UFUNCTION(BlueprintCallable, Category = "Inventory|Items")
	TMap<int32, FWeaponInstance> GetAllWeaponMap() const;
	UFUNCTION(BlueprintCallable, Category = "Inventory|Items")
	TMap<int32, FGearInstance> GetAllGearMap() const;
	UFUNCTION(BlueprintCallable, Category = "Inventory|Items")
	int32 GetInventorySize() const;
	UFUNCTION(BlueprintCallable, Category = "Inventory|Items")
	void SetInventorySize(int32 NewSize);
	UFUNCTION(BlueprintCallable, Category = "Inventory|Items")
	int32 GetMoney() const;
	UFUNCTION(BlueprintCallable, Category = "Inventory|Items")
	void SetMoney(int32 NewMoney);
	UFUNCTION(BlueprintCallable, Category = "Inventory|Items")
	int32 GetNextWeaponID() const;
	UFUNCTION(BlueprintCallable, Category = "Inventory|Items")
	int32 GetNextGearID() const;
	//~ 结束暴露给蓝图的接口
private:
	UPROPERTY()
	UInventoryComponent* Inventory = nullptr;
	
};
