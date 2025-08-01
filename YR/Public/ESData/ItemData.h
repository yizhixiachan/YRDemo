// Copyright © 2025 yizhixiachan

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PaperSprite.h"

#include "ItemData.generated.h"

//~ 开始枚举

/** 物品类型 */
UENUM(BlueprintType)
enum class EItemType : uint8
{
	IT_EMAX			UMETA(DisplayName = EMAX),
	IT_Weapon		UMETA(DisplayName = Weapon),
	IT_Gear			UMETA(DisplayName = Gear),
	IT_Consumable	UMETA(DisplayName = Consumable),
	IT_Quest		UMETA(DisplayName = Quest),
};
/** 声明枚举遍历范围 */
ENUM_RANGE_BY_COUNT(EItemType, EItemType::IT_Quest);

/**稀有度类型 */ 
UENUM(BlueprintType)
enum class ERarityType : uint8
{
	RT_EMAX			UMETA(DisplayName = EMAX),
	RT_Normal		UMETA(DisplayName = Normal),
	RT_Excellent	UMETA(DisplayName = Excellent),
	RT_Superior		UMETA(DisplayName = Superior),
	RT_Epic			UMETA(DisplayName = Epic),
	RT_Legendary	UMETA(DisplayName = Lengendary),
	RT_Artifact		UMETA(DisplayName = Artifact)
};

/**武器类型 */ 
UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	WT_EMAX		UMETA(DisplayName = EMAX),
	WT_Sword	UMETA(DisplayName = Sword),
	WT_Bow		UMETA(DisplayName = Bow),
	WT_Staff	UMETA(DisplayName = Staff)
};

/**防具类型 */
UENUM(BlueprintType)
enum class EGearType : uint8
{
	GT_EMAX			UMETA(DisplayName = EMAX),
	GT_Helmet		UMETA(DisplayName = Helmet),
	GT_Armor		UMETA(DisplayName = Armor),
	GT_Boots		UMETA(DisplayName = Boots),
	GT_Accessories	UMETA(DisplayName = Accessories)
};

/**消耗品效果 */
UENUM(BlueprintType)
enum class EConsumableEffect : uint8
{
	CE_EMAX				UMETA(DisplayName = EMAX),
	CE_RestoreHP		UMETA(DisplayName = RestoreHP),
	CE_RestoreMP		UMETA(DisplayName = RestoreMP)
};

/**武器属性 */
UENUM(BlueprintType)
enum class EWeaponAttribute : uint8
{
	WA_EMAX				UMETA(DisplayName = EMAX),
	WA_ExtraATK			UMETA(DisplayName = ExtraATK),
	WA_ExtraMP			UMETA(DisplayName = ExtraMP),
	WA_ExtraCRIT_Rate	UMETA(DisplayName = ExtraCRIT_Rate),
	WA_ExtraCRIT_DMG	UMETA(DisplayName = ExtraCRIT_DMG)
};

/**防具属性 */
UENUM(BlueprintType)
enum class EGearAttribute : uint8
{
	GA_EMAX				UMETA(DisplayName = EMAX),
	GA_ExtraHP			UMETA(DisplayName = ExtraHP),
	GA_ExtraMP			UMETA(DisplayName = ExtraMP),
	GA_ExtraDEF			UMETA(DisplayName = ExtraDEF)
};

//~ 结束枚举

//~ 开始结构体

/**装备随机属性上下限 */
USTRUCT(BlueprintType)
struct FRangeValue : public FTableRowBase
{
	GENERATED_BODY()

public:
	float GetRandomValue() const { return FMath::FRandRange(MinVal, MaxVal); }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MinVal = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxVal = 0.0f;
};

/**静态武器表 */ 
USTRUCT(BlueprintType)
struct FWeaponRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 ID = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UPaperSprite> Icon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UStaticMesh> WeaponMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EWeaponType WeaponType{ EWeaponType::WT_EMAX };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Intro;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EWeaponAttribute, FRangeValue> WeaponAttribute;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ERarityType Rarity{ ERarityType::RT_EMAX };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Price = 0;

};

/**静态防具表 */
USTRUCT(BlueprintType)
struct FGearRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 ID = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UPaperSprite> Icon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EGearType GearType{ EGearType::GT_EMAX };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Intro;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EGearAttribute, FRangeValue> GearAttribute;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ERarityType Rarity{ ERarityType::RT_EMAX };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Price = 0;

};

/**静态消耗道具表 */
USTRUCT(BlueprintType)
struct FConsumableItemRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 ID = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UPaperSprite> Icon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Intro;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EConsumableEffect, float> ConsumableEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ERarityType Rarity{ ERarityType::RT_EMAX };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Price = 0;
};

/**静态任务道具表 */ 
USTRUCT(BlueprintType)
struct FQuestItemRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 ID = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UPaperSprite> Icon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Intro;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ERarityType Rarity{ ERarityType::RT_EMAX };
};

USTRUCT(BlueprintType)
struct FItemTableRow
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	EItemType ItemType;

	UPROPERTY(BlueprintReadOnly)
	FWeaponRow WeaponRow;

	UPROPERTY(BlueprintReadOnly)
	FGearRow GearRow;

	UPROPERTY(BlueprintReadOnly)
	FConsumableItemRow ConsumableItemRow;

	UPROPERTY(BlueprintReadOnly)
	FQuestItemRow QuestItemRow;
};
//~ 结束结构体
