// Copyright © 2025 yizhixiachan

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ESData/BackpackData.h"
#include "Utilities/FL_YR.h"

#include "DummyData.generated.h"

/**职业类型 */
UENUM(BlueprintType)
enum class ERoleType : uint8
{
	RT_EMAX		UMETA(DisplayName = EMAX),
	RT_War		UMETA(DisplayName = War),
	RT_Hunter	UMETA(DisplayName = Hunter),
	RT_Mage		UMETA(DisplayName = Mage)
};

/**装备槽 */
USTRUCT(BlueprintType)
struct FEquipmentSlots
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FItemUID WeaponSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FItemUID HelmetSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FItemUID ArmorSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FItemUID BootsSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FItemUID AccessoriesSlot;
};

/**静态人物数据 */
USTRUCT(BlueprintType)
struct YR_API FDummyRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 ID = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ERoleType RoleType{ ERoleType::RT_EMAX };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Intro;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> Avatar = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSoftClassPtr<ACharacter> CharBP = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxHP = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxMP = 50.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ATK = 50.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float DEF = 20.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float CRIT_Rate = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float CRIT_DMG = 0.0f;

};

/**动态人物数据 */
USTRUCT(BlueprintType)
struct YR_API FDummyAttributes
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Level = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxEXP = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float EXP = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxHP = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float HP = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxMP = 50.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MP = 50.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float ATK = 50.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float DEF = 20.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float CRIT_Rate = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float CRIT_DMG = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FEquipmentSlots EquipmentSlots;

public:
	float GetEXP() const { return EXP; }
	void SetEXP(float NewEXP)
	{
		EXP = NewEXP;
		while (EXP >= MaxEXP)
		{
			Level++;
			MaxHP += 20;
			HP = MaxHP;
			MaxMP += 10;
			MP = MaxMP;
			ATK += 5;
			DEF += 3;
			CRIT_Rate += 0.01;
			CRIT_DMG += 0.05;

			EXP -= MaxEXP;
			MaxEXP = UFL_YR::FLib_GetMaxEXP(Level);
		}

	}

	float GetMaxHP() const { return MaxHP; }
	void SetMaxHP(float NewMaxHP)
	{
		MaxHP = NewMaxHP;
		if (MaxHP < HP) HP = MaxHP;
	}

	float GetHP() const { return HP; }
	void SetHP(float NewHP)
	{
		HP = NewHP;
		if (HP > MaxHP) HP = MaxHP;
		if (HP < 0) HP = 0;
	}

	float GetMaxMP() const { return MaxMP; }
	void SetMaxMP(float NewMaxMP)
	{
		MaxMP = NewMaxMP;
		if (MaxMP < MP) MP = MaxMP;
	}

	float GetMP() const { return MP; }
	void SetMP(float NewMP)
	{
		MP = NewMP;
		if (MP > MaxMP) MP = MaxMP;
		if (MP < 0) MP = 0;
	}

	float GetATK() const { return ATK; }
	void SetATK(float NewATK) { ATK = NewATK; }

	float GetDEF() const { return DEF; }
	void SetDEF(float NewDEF) { DEF = NewDEF; }

	float GetCRIT_Rate() const { return CRIT_Rate; }
	void SetCRIT_Rate(float NewCRIT_Rate) { CRIT_Rate = NewCRIT_Rate; }

	float GetCRIT_DMG() const { return CRIT_DMG; }
	void SetCRIT_DMG(float NewCRIT_DMG) { CRIT_DMG = NewCRIT_DMG; }

	FEquipmentSlots GetEquipmentSlots() const { return EquipmentSlots; }

	void SetWeaponSlot(FItemUID Weapon) { EquipmentSlots.WeaponSlot = Weapon; }
	void SetHelmetSlot(FItemUID Helmet) { EquipmentSlots.HelmetSlot = Helmet; }
	void SetArmorSlot(FItemUID Armor) { EquipmentSlots.ArmorSlot = Armor; }
	void SetBootsSlot(FItemUID Boots) { EquipmentSlots.BootsSlot = Boots; }
	void SetAccessorySlot(FItemUID Accessory) { EquipmentSlots.AccessoriesSlot = Accessory; }

};