// Copyright © 2025 yizhixiachan


#include "Subsystem/InventorySubsystem.h"
#include "Components/InventoryComponent.h"
#include "System/YRPlayerController.h"
#include "System/YRPlayerState.h"

bool UInventorySubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	Super::ShouldCreateSubsystem(Outer);
	return true;
}

void UInventorySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	Inventory = NewObject<UInventoryComponent>(this);
}

void UInventorySubsystem::Deinitialize()
{
	Inventory = nullptr;

	Super::Deinitialize();
}

const UInventoryComponent* UInventorySubsystem::GetInventory() const
{
	return Inventory;
}

void UInventorySubsystem::InitializeDataTables(
	UDataTable* InWeaponTable, 
	UDataTable* InGearTable, 
	UDataTable* InConsumableItemTable, 
	UDataTable* InQuestItemTable)
{
	Inventory->InitializeDataTables(
		InWeaponTable, 
		InGearTable, 
		InConsumableItemTable, 
		InQuestItemTable);
}

void UInventorySubsystem::InitializeInventoryData(
	TMap<FItemUID, int32> InAllItemMap, 
	TMap<int32, FWeaponInstance> InAllWeaponMap, 
	TMap<int32, FGearInstance> InAllGearMap, 
	int32 InInventorySize, 
	int32 InMoney, 
	int32 InNextWeaponID, 
	int32 InNextGearID)
{
	Inventory->InitializeInventoryData(
		InAllItemMap,
		InAllWeaponMap, 
		InAllGearMap, 
		InInventorySize, 
		InMoney, 
		InNextWeaponID, 
		InNextGearID);
}

bool UInventorySubsystem::AddOrBuyItem(FItemUID ItemUID, int32 Count, bool IsBuy)
{
	return Inventory->AddOrBuyItem(ItemUID, Count, IsBuy);
}

bool UInventorySubsystem::RemoveOrSaleItem(FItemUID ItemUID, int32 Count, bool IsSale)
{
	return Inventory->RemoveOrSaleItem(ItemUID, Count, IsSale);
}

bool UInventorySubsystem::ItemTrade(FItemUID ItemUID, int32 Count, bool IsBuy)
{
	return Inventory->ItemTrade(ItemUID, Count, IsBuy);
}

int32 UInventorySubsystem::GetPriceByItemUID(FItemUID ItemUID, bool IsDirect) const
{
	return Inventory->GetPriceByItemUID(ItemUID, IsDirect);
}

FItemTableRow UInventorySubsystem::GetItemRow(FItemUID ItemUID, bool IsDirect) const
{
	FItemTableRow Result;
	Result.ItemType = ItemUID.ItemType;

	switch (ItemUID.ItemType)
	{
	case EItemType::IT_Weapon:
		if (IsDirect) break;
		if (FWeaponRow* Row = Inventory->GetItemRowByItemUID<FWeaponRow>(ItemUID))
			Result.WeaponRow = *Row;
		break;
	case EItemType::IT_Gear:
		if (IsDirect) break;
		if (FGearRow* Row = Inventory->GetItemRowByItemUID<FGearRow>(ItemUID))
			Result.GearRow = *Row;
		break;
	case EItemType::IT_Consumable:
		if (FConsumableItemRow* Row = Inventory->GetItemRowByItemUID<FConsumableItemRow>(ItemUID))
			Result.ConsumableItemRow = *Row;
		break;
	case EItemType::IT_Quest:
		if (FQuestItemRow* Row = Inventory->GetItemRowByItemUID<FQuestItemRow>(ItemUID))
			Result.QuestItemRow = *Row;
		break;
	default:
		break;
	}
	return Result;
}

FWeaponRow UInventorySubsystem::GetWeaponRowByItemUID(FItemUID ItemUID) const
{
	return *Inventory->GetWeaponRowByItemUID(ItemUID);
}

FGearRow UInventorySubsystem::GetGearRowByItemUID(FItemUID ItemUID) const
{
	return *Inventory->GetGearRowByItemUID(ItemUID);
}

void UInventorySubsystem::GenerateAndAddWeapon(TMap<EWeaponAttribute, FRangeValue> WeaponAttribute, int32 OID)
{
	Inventory->GenerateAndAddWeapon(WeaponAttribute, OID);
}

void UInventorySubsystem::GenerateAndAddGear(TMap<EGearAttribute, FRangeValue> GearAttribute, int32 OID)
{
	Inventory->GenerateAndAddGear(GearAttribute, OID);
}

void UInventorySubsystem::Equip(FItemUID ItemUID)
{
	AYRPlayerController* PC = GetWorld()->GetFirstPlayerController<AYRPlayerController>();
	if (!PC) return;
	AYRPlayerState* PS = PC->GetPlayerState<AYRPlayerState>();
	if (!PS) return;

	Inventory->Equip(ItemUID, PS->AllCharAttributeMap, PS->CurCharIndex);
}

void UInventorySubsystem::Unequip(FItemUID ItemUID)
{
	AYRPlayerController* PC = GetWorld()->GetFirstPlayerController<AYRPlayerController>();
	if (!PC) return;
	AYRPlayerState* PS = PC->GetPlayerState<AYRPlayerState>();
	if (!PS) return;

	Inventory->Unequip(ItemUID, PS->AllCharAttributeMap, PS->CurCharIndex);
}

void UInventorySubsystem::UseConsumable(FItemUID ItemUID, int32 Count)
{
	AYRPlayerController* PC = GetWorld()->GetFirstPlayerController<AYRPlayerController>();
	if (!PC) return;
	AYRPlayerState* PS = PC->GetPlayerState<AYRPlayerState>();
	if (!PS) return;

	Inventory->UseConsumable(ItemUID, PS->AllCharAttributeMap, PS->CurCharIndex, Count);
}

TMap<FItemUID, int32> UInventorySubsystem::GetClassifiedItemMap(EItemType ItemType) const
{
	return Inventory->GetClassifiedItemMap(ItemType);
}

TMap<FItemUID, int32> UInventorySubsystem::GetAllItemMap() const
{
	return Inventory->GetAllItemMap();
}

TMap<int32, FWeaponInstance> UInventorySubsystem::GetAllWeaponMap() const
{
	return Inventory->GetAllWeaponMap();
}

TMap<int32, FGearInstance> UInventorySubsystem::GetAllGearMap() const
{
	return Inventory->GetAllGearMap();
}

int32 UInventorySubsystem::GetInventorySize() const
{
	return Inventory->GetInventorySize();
}

void UInventorySubsystem::SetInventorySize(int32 NewSize)
{
	Inventory->SetInventorySize(NewSize);
}

int32 UInventorySubsystem::GetMoney() const
{
	return Inventory->GetMoney();
}

void UInventorySubsystem::SetMoney(int32 NewMoney)
{
	Inventory->SetMoney(NewMoney);
}

int32 UInventorySubsystem::GetNextWeaponID() const
{
	return Inventory->GetNextWeaponID();
}

int32 UInventorySubsystem::GetNextGearID() const
{
	return Inventory->GetNextGearID();
}

