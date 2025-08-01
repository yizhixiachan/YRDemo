// Copyright © 2025 yizhixiachan

#pragma once

#include "CoreMinimal.h"
#include "ESData/ItemData.h"

#include "BackpackData.generated.h"


/**武器实例 */ 
USTRUCT(BlueprintType)
struct FWeaponInstance
{
	GENERATED_BODY()

public:
	FWeaponInstance() = default;

	FWeaponInstance(int32 InID, int32 InOID, TMap<EWeaponAttribute, float> InWeaponAttribute)
		: ID(InID)
		, OID(InOID)
		, WeaponAttribute(InWeaponAttribute)
	{
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 ID = -1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 OID = -1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EWeaponAttribute, float> WeaponAttribute;

};

/**防具实例 */ 
USTRUCT(BlueprintType)
struct FGearInstance
{
	GENERATED_BODY()

public:
	FGearInstance() = default;
	FGearInstance(int32 InID, int32 InOID, TMap<EGearAttribute, float> InGearAttribute)
		: ID(InID)
		, OID(InOID)
		, GearAttribute(InGearAttribute)
	{
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 ID = -1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 OID = -1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EGearAttribute, float> GearAttribute;

};

/**物品UniqueID */
USTRUCT(BlueprintType)
struct FItemUID
{
	GENERATED_BODY()

public:
	FItemUID() = default;
	FItemUID(EItemType InItemType, int32 InID) 
		: ItemType(InItemType)
		, ID(InID) 
	{
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EItemType ItemType{ EItemType::IT_EMAX };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 ID = -1;

	/**重载 == 运算符用于比较 */ 
	bool operator==(const FItemUID& Other) const
	{
		return ItemType == Other.ItemType && ID == Other.ID;
	}

	/**生成哈希值（用于TMap）*/ 
	friend uint32 GetTypeHash(const FItemUID& Key)
	{
		return HashCombine(
			GetTypeHash(Key.ItemType),
			GetTypeHash(Key.ID)
		);
	}
};
