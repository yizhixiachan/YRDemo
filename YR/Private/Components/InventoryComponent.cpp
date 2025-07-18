// Copyright © 2025 yizhixiachan


#include "Components/InventoryComponent.h"

void UInventoryComponent::InitializeDataTables(
	UDataTable* InWeaponTable, 
	UDataTable* InGearTable, 
	UDataTable* InConsumableItemTable, 
	UDataTable* InQuestItemTable)
{
	WeaponTable = InWeaponTable;
	GearTable = InGearTable;
	ConsumableItemTable = InConsumableItemTable;
	QuestItemTable = InQuestItemTable;
}

void UInventoryComponent::InitializeInventoryData(
	TMap<FItemUID, int32> InAllItemMap, 
	TMap<int32, FWeaponInstance> InAllWeaponMap, 
	TMap<int32, FGearInstance> InAllGearMap, 
	int32 InInventorySize, 
	int32 InMoney,
	int32 InNextWeaponID, 
	int32 InNextGearID)
{
	AllItemMap = InAllItemMap;
	AllWeaponMap = InAllWeaponMap;
	AllGearMap = InAllGearMap;
	InventorySize = InInventorySize;
	Money = InMoney;
	NextWeaponID = InNextWeaponID;
	NextGearID = InNextGearID;
}

bool UInventoryComponent::AddOrBuyItem(FItemUID ItemUID, int32 Count, bool IsBuy)
{
	/**背包容量不足直接退出 */
	if (AllItemMap.Num()+1 > InventorySize) return false;

	/**Case1 背包中有该物品 */
	if (AllItemMap.Contains(ItemUID))
	{
		if (IsBuy)
		{
			/**钱不够直接退出 */
			if (!ItemTrade(ItemUID, Count, true)) return false;
		}

		int32* ItemCountPtr = AllItemMap.Find(ItemUID);
		*ItemCountPtr += Count;
		return true;
	}
	/**Case2 背包中没有该物品 */
	else
	{
		if (IsBuy)
		{
			/**钱不够直接退出 */
			if (!ItemTrade(ItemUID, Count, true)) return false;
		}

		AllItemMap.Add(ItemUID, Count);
		return true;
	}

}

bool UInventoryComponent::RemoveOrSaleItem(FItemUID ItemUID, int32 Count, bool IsSale)
{
	/**背包中没有该物品直接退出 */
	if (!AllItemMap.Contains(ItemUID)) return false;

	int32* ItemCountPtr = AllItemMap.Find(ItemUID);
	if (*ItemCountPtr > Count)
	{
		*ItemCountPtr -= Count;
	}
	else if(*ItemCountPtr == Count)
	{
		AllItemMap.Remove(ItemUID);
	}
	else
	{
		return false;
	}

	/**如果是出售，还需要增加Money */ 
	if (IsSale)
	{

		if (!ItemTrade(ItemUID, Count, false)) return false;
	}

	/**如果是装备，还要从装备Map中删除 */
	if (ItemUID.ItemType == EItemType::IT_Weapon)
	{
		AllWeaponMap.Remove(ItemUID.ID);
	}
	if (ItemUID.ItemType == EItemType::IT_Gear)
	{
		AllGearMap.Remove(ItemUID.ID);
	}

	return true;

}

int32 UInventoryComponent::GetPriceByItemUID(FItemUID ItemUID, bool IsDirect) const
{
	static const FString ContextString("GetPriceByItemUID");
	FName RowName = FName(*FString::FromInt(ItemUID.ID));

	switch (ItemUID.ItemType)
	{
	case EItemType::IT_EMAX:
		break;
	case EItemType::IT_Weapon:
		if (IsDirect)
		{
			return WeaponTable->FindRow<FWeaponRow>(RowName, ContextString)->Price;
		}
		else
		{
			RowName = FName(*FString::FromInt(AllWeaponMap.Find(ItemUID.ID)->OID));
			return WeaponTable->FindRow<FWeaponRow>(RowName, ContextString)->Price;
		}
		break;
	case EItemType::IT_Gear:
		if (IsDirect)
		{
			return GearTable->FindRow<FGearRow>(RowName, ContextString)->Price;
		}
		else
		{
			RowName = FName(*FString::FromInt(AllGearMap.Find(ItemUID.ID)->OID));
			return GearTable->FindRow<FGearRow>(RowName, ContextString)->Price;
		}
		break;
	case EItemType::IT_Consumable:
		return ConsumableItemTable->FindRow<FConsumableItemRow>(RowName, ContextString)->Price;
		break;
	default:
		break;
	}
	return -1;
}

bool UInventoryComponent::ItemTrade(FItemUID ItemUID, int32 Count, bool IsBuy)
{
	int32 Price = 0;
	if (IsBuy)
	{
		switch (ItemUID.ItemType)
		{
		case EItemType::IT_Weapon:
			Price = GetPriceByItemUID(ItemUID, true);
			if (Price <= 0 || Money < Price * Count) return false;
			Money -= Price * Count;
			break;
		case EItemType::IT_Gear:
			Price = GetPriceByItemUID(ItemUID, true);
			if (Price <= 0 || Money < Price * Count) return false;
			Money -= Price * Count;
			break;
		case EItemType::IT_Consumable:
			Price = GetPriceByItemUID(ItemUID, false);
			if (Price <= 0 || Money < Price * Count) return false;
			Money -= Price * Count;
			break;
		default:
			return false;
			break;
		}
		return true;
	}
	else
	{
		switch (ItemUID.ItemType)
		{
		case EItemType::IT_Weapon:
			Price = GetPriceByItemUID(ItemUID, false);
			if (Price > 0)
				Money += Price * Count;
			break;
		case EItemType::IT_Gear:
			Price = GetPriceByItemUID(ItemUID, false);
			if (Price > 0)
				Money += Price * Count;
			break;
		case EItemType::IT_Consumable:
			Price = GetPriceByItemUID(ItemUID, false);
			if (Price > 0)
				Money += Price * Count;
			break;
		default:
			return false;
			break;
		}
		return true;
	}

}

void UInventoryComponent::GenerateAndAddWeapon(TMap<EWeaponAttribute, FRangeValue> WeaponAttribute, int32 OID)
{
	int32 ID = NextWeaponID++;
	TMap<EWeaponAttribute, float> FinalAttribute;

	/**武器属性加成初始化 */ 
	for (const auto& ArrayElem : WeaponAttribute)
	{
		float Val = ArrayElem.Value.GetRandomValue();
		FinalAttribute.Add(ArrayElem.Key, Val);
	}

	AllWeaponMap.Add(ID, FWeaponInstance(ID, OID, FinalAttribute));
	AllItemMap.Add(FItemUID(EItemType::IT_Weapon, ID), 1);
}

void UInventoryComponent::GenerateAndAddGear(TMap<EGearAttribute, FRangeValue> GearAttribute, int32 OID)
{
	int32 ID = NextGearID++;
	TMap<EGearAttribute, float> FinalAttribute;

	/**防具属性加成初始化 */
	for (const auto& ArrayElem : GearAttribute)
	{
		float Val = ArrayElem.Value.GetRandomValue();
		FinalAttribute.Add(ArrayElem.Key, Val);
	}

	AllGearMap.Add(ID, FGearInstance(ID, OID, FinalAttribute));
	AllItemMap.Add(FItemUID(EItemType::IT_Gear, ID), 1);
}

void UInventoryComponent::Equip(FItemUID ItemUID, TMap<int32, FDummyAttributes>& AllCharAttrMap, int32 CurCharIndex)
{
	/**装备武器 */ 
	if (ItemUID.ItemType == EItemType::IT_Weapon)
	{
		if (!AllWeaponMap.Contains(ItemUID.ID)) return;

		FWeaponInstance* WeaponInstPtr = AllWeaponMap.Find(ItemUID.ID);

		/**角色获得武器加成 */ 
		for (const auto& EffectPair : WeaponInstPtr->WeaponAttribute)
		{
			switch (EffectPair.Key)
			{
			case EWeaponAttribute::WA_ExtraATK:
				AllCharAttrMap[CurCharIndex].SetATK(AllCharAttrMap[CurCharIndex].GetATK() + EffectPair.Value);
				break;
			case EWeaponAttribute::WA_ExtraMP:
				AllCharAttrMap[CurCharIndex].SetMaxMP(AllCharAttrMap[CurCharIndex].GetMaxMP() + EffectPair.Value);
				break;
			case EWeaponAttribute::WA_ExtraCRIT_Rate:
				AllCharAttrMap[CurCharIndex].SetCRIT_Rate(AllCharAttrMap[CurCharIndex].GetCRIT_Rate() + EffectPair.Value);
				break;
			case EWeaponAttribute::WA_ExtraCRIT_DMG:
				AllCharAttrMap[CurCharIndex].SetCRIT_DMG(AllCharAttrMap[CurCharIndex].GetCRIT_DMG() + EffectPair.Value);
				break;
			default:
				break;
			}
		}
		/**如果此时装有武器，先卸下 */
		if (AllCharAttrMap[CurCharIndex].EquipmentSlots.WeaponSlot.ID != -1)
			Unequip(AllCharAttrMap[CurCharIndex].EquipmentSlots.WeaponSlot, AllCharAttrMap, CurCharIndex);

		/**设置角色武器插槽 */
		AllCharAttrMap[CurCharIndex].SetWeaponSlot(ItemUID);
	}

	/**装备防具 */
	if (ItemUID.ItemType == EItemType::IT_Gear)
	{
		if (!AllGearMap.Contains(ItemUID.ID)) return;
		const FGearRow* FoundRow = GetItemRowByItemUID<FGearRow>(ItemUID);
		if (!FoundRow) return;

		FGearInstance* GearInst = AllGearMap.Find(ItemUID.ID);

		/**角色获得防具加成 */
		for (const auto& EffectPair : GearInst->GearAttribute)
		{
			switch (EffectPair.Key)
			{
			case EGearAttribute::GA_ExtraHP:
				AllCharAttrMap[CurCharIndex].SetMaxHP(AllCharAttrMap[CurCharIndex].GetMaxHP() + EffectPair.Value);
				break;
			case EGearAttribute::GA_ExtraMP:
				AllCharAttrMap[CurCharIndex].SetMaxMP(AllCharAttrMap[CurCharIndex].GetMaxMP() + EffectPair.Value);
				break;
			case EGearAttribute::GA_ExtraDEF:
				AllCharAttrMap[CurCharIndex].SetDEF(AllCharAttrMap[CurCharIndex].GetDEF() + EffectPair.Value);
				break;
			default:
				break;
			}
		}

		/**根据防具类型设置角色防具插槽 */
		switch (FoundRow->GearType)
		{
		case EGearType::GT_Helmet:
			if (AllCharAttrMap[CurCharIndex].EquipmentSlots.HelmetSlot.ID != -1) 
				Unequip(AllCharAttrMap[CurCharIndex].EquipmentSlots.HelmetSlot, AllCharAttrMap, CurCharIndex);
			AllCharAttrMap[CurCharIndex].SetHelmetSlot(ItemUID);
			break;
		case EGearType::GT_Armor:
			if (AllCharAttrMap[CurCharIndex].EquipmentSlots.ArmorSlot.ID != -1) 
				Unequip(AllCharAttrMap[CurCharIndex].EquipmentSlots.ArmorSlot, AllCharAttrMap, CurCharIndex);
			AllCharAttrMap[CurCharIndex].SetArmorSlot(ItemUID);
			break;
		case EGearType::GT_Boots:
			if (AllCharAttrMap[CurCharIndex].EquipmentSlots.BootsSlot.ID != -1) 
				Unequip(AllCharAttrMap[CurCharIndex].EquipmentSlots.BootsSlot, AllCharAttrMap, CurCharIndex);
			AllCharAttrMap[CurCharIndex].SetBootsSlot(ItemUID);
			break;
		case EGearType::GT_Accessories:
			if (AllCharAttrMap[CurCharIndex].EquipmentSlots.AccessoriesSlot.ID != -1) 
				Unequip(AllCharAttrMap[CurCharIndex].EquipmentSlots.AccessoriesSlot, AllCharAttrMap, CurCharIndex);
			AllCharAttrMap[CurCharIndex].SetAccessorySlot(ItemUID);
			break;
		default:
			break;
		}
	}

	/**从背包中删除 */
	AllItemMap.Remove(ItemUID);

}

void UInventoryComponent::Unequip(FItemUID ItemUID, TMap<int32, FDummyAttributes>& AllCharAttrMap, int32 CurCharIndex)
{
	/**卸下武器 */
	if (ItemUID.ItemType == EItemType::IT_Weapon)
	{
		if (!AllWeaponMap.Contains(ItemUID.ID)) return;

		FWeaponInstance* WeaponInstPtr = AllWeaponMap.Find(ItemUID.ID);

		/**角色失去武器加成 */
		for (const auto& EffectPair : WeaponInstPtr->WeaponAttribute)
		{
			switch (EffectPair.Key)
			{
			case EWeaponAttribute::WA_ExtraATK:
				AllCharAttrMap[CurCharIndex].SetATK(AllCharAttrMap[CurCharIndex].GetATK() - EffectPair.Value);
				break;
			case EWeaponAttribute::WA_ExtraMP:
				AllCharAttrMap[CurCharIndex].SetMaxMP(AllCharAttrMap[CurCharIndex].GetMaxMP() - EffectPair.Value);
				break;
			case EWeaponAttribute::WA_ExtraCRIT_Rate:
				AllCharAttrMap[CurCharIndex].SetCRIT_Rate(AllCharAttrMap[CurCharIndex].GetCRIT_Rate() - EffectPair.Value);
				break;
			case EWeaponAttribute::WA_ExtraCRIT_DMG:
				AllCharAttrMap[CurCharIndex].SetCRIT_DMG(AllCharAttrMap[CurCharIndex].GetCRIT_DMG() - EffectPair.Value);
				break;
			default:
				break;
			}
		}
		/**设置角色武器插槽为空 */
		AllCharAttrMap[CurCharIndex].SetWeaponSlot(FItemUID());

		/**放进背包中 */
		AllItemMap.Add(ItemUID, 1);
	}

	/**卸下防具 */
	if (ItemUID.ItemType == EItemType::IT_Gear)
	{
		if (!AllGearMap.Contains(ItemUID.ID)) return;
		const FGearRow* FoundRow = GetItemRowByItemUID<FGearRow>(ItemUID);
		if (!FoundRow) return;

		FGearInstance* GearInstPtr = AllGearMap.Find(ItemUID.ID);

		/**角色失去防具加成 */
		for (const auto& EffectPair : GearInstPtr->GearAttribute)
		{
			switch (EffectPair.Key)
			{
			case EGearAttribute::GA_ExtraHP:
				AllCharAttrMap[CurCharIndex].SetMaxHP(AllCharAttrMap[CurCharIndex].GetMaxHP() - EffectPair.Value);
				break;
			case EGearAttribute::GA_ExtraMP:
				AllCharAttrMap[CurCharIndex].SetMaxMP(AllCharAttrMap[CurCharIndex].GetMaxMP() - EffectPair.Value);
				break;
			case EGearAttribute::GA_ExtraDEF:
				AllCharAttrMap[CurCharIndex].SetDEF(AllCharAttrMap[CurCharIndex].GetDEF() - EffectPair.Value);
				break;
			default:
				break;
			}
		}

		/**根据防具类型设置角色防具插槽为空 */
		switch (FoundRow->GearType)
		{
		case EGearType::GT_Helmet:
			AllCharAttrMap[CurCharIndex].SetHelmetSlot(FItemUID());
			break;
		case EGearType::GT_Armor:
			AllCharAttrMap[CurCharIndex].SetArmorSlot(FItemUID());
			break;
		case EGearType::GT_Boots:
			AllCharAttrMap[CurCharIndex].SetBootsSlot(FItemUID());
			break;
		case EGearType::GT_Accessories:
			AllCharAttrMap[CurCharIndex].SetAccessorySlot(FItemUID());
			break;
		default:
			break;
		}

		/**放进背包中 */
		AllItemMap.Add(ItemUID, 1);
	}

}

void UInventoryComponent::UseConsumable(FItemUID ItemUID, TMap<int32, FDummyAttributes>& AllCharAttrMap, int32 CurCharIndex, int32 Count)
{
	const FConsumableItemRow* FoundRow = GetItemRowByItemUID<FConsumableItemRow>(ItemUID);
	if (!FoundRow) return;
	if(!AllItemMap.Contains(ItemUID)) return;

	int32* ItemCountPtr = AllItemMap.Find(ItemUID);
	if (*ItemCountPtr < Count) return;

	/**应用道具效果 */
	for (const auto& EffectPair : FoundRow->ConsumableEffect)
	{
		switch (EffectPair.Key)
		{
		case EConsumableEffect::CE_EMAX:
			break;
		case EConsumableEffect::CE_RestoreHP:
			AllCharAttrMap[CurCharIndex].SetHP(AllCharAttrMap[CurCharIndex].GetHP() + EffectPair.Value * Count);
			break;
		case EConsumableEffect::CE_RestoreMP:
			AllCharAttrMap[CurCharIndex].SetMP(AllCharAttrMap[CurCharIndex].GetMP() + EffectPair.Value * Count);
			break;
		default:
			break;
		}
	}

	RemoveOrSaleItem(ItemUID, Count);

}

TMap<FItemUID, int32> UInventoryComponent::GetClassifiedItemMap(EItemType ItemType) const
{
	TMap<FItemUID, int32> ClassifiedItemTMap;

	switch (ItemType)
	{
	case EItemType::IT_Weapon:
		for (const auto& ArrayElem : AllItemMap)
		{
			if (ArrayElem.Key.ItemType == ItemType)
				ClassifiedItemTMap.Add(ArrayElem);
		}
		break;
	case EItemType::IT_Gear:
		for (const auto& ArrayElem : AllItemMap)
		{
			if (ArrayElem.Key.ItemType == ItemType)
				ClassifiedItemTMap.Add(ArrayElem);
		}
		break;
	case EItemType::IT_Consumable:
		for (const auto& ArrayElem : AllItemMap)
		{
			if (ArrayElem.Key.ItemType == ItemType)
				ClassifiedItemTMap.Add(ArrayElem);
		}
		break;
	case EItemType::IT_Quest:
		for (const auto& ArrayElem : AllItemMap)
		{
			if (ArrayElem.Key.ItemType == ItemType)
				ClassifiedItemTMap.Add(ArrayElem);
		}
		break;
	default:
		break;
	}

	return ClassifiedItemTMap;
}
