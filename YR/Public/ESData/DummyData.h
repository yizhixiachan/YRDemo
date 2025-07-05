// Copyright © 2025 yizhixiachan

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Utilities/FL_YR.h"

#include "DummyData.generated.h"

// 职业类型
UENUM(BlueprintType)
enum class ERoleType : uint8
{
	RT_EMAX		UMETA(DisplayName = EMAX),
	RT_War		UMETA(DisplayName = War),
	RT_Hunter	UMETA(DisplayName = Hunter),
	RT_Mage		UMETA(DisplayName = Mage)
};

USTRUCT(BlueprintType)
struct YR_API FDummyData
{
	GENERATED_BODY()

private:
	int32 Level;
	float MaxEXP;
	float EXP;
	float MaxHP;
	float HP;
	float MaxMP;
	float MP;
	float ATK;
	float DEF;
	float CRIT_Rate;
	float CRIT_DMG;

public:
	int32 GetEXP() const { return EXP; }
	void SetEXP(int32 NewEXP)
	{
		EXP = NewEXP;
		while (EXP >= MaxEXP)
		{
			Level++;
			EXP = MaxEXP - EXP;
			MaxEXP = UFL_YR::GetMaxEXPForLevel(Level);
		}

	}

	int32 GetMaxHP() const { return MaxHP; }
	void SetMaxHP(int32 NewMaxHP)
	{
		MaxHP = NewMaxHP;
		if (MaxHP < HP) HP = MaxHP;
	}

	int32 GetHP() const { return HP; }
	void SetHP(int32 NewHP)
	{
		HP = NewHP;
		if (HP > MaxHP) HP = MaxHP;
		if (HP < 0) HP = 0;
	}

	int32 GetMaxMP() const { return MaxMP; }
	void SetMaxMP(int32 NewMaxMP)
	{
		MaxMP = NewMaxMP;
		if (MaxMP < MP) MP = MaxMP;
	}

	int32 GetMP() const { return MP; }
	void SetMP(int32 NewMP)
	{
		MP = NewMP;
		if (MP > MaxMP) MP = MaxMP;
		if (MP < 0) MP = 0;
	}

	int32 GetATK() const { return ATK; }
	void SetATK(int32 NewATK) { ATK = NewATK; }

	int32 GetDEF() const { return DEF; }
	void SetDEF(int32 NewDEF) { DEF = NewDEF; }

	float GetCRIT_Rate() const { return CRIT_Rate; }
	void SetCRIT_Rate(float NewCRIT_Rate) { CRIT_Rate = NewCRIT_Rate; }

	float GetCRIT_DMG() const { return CRIT_DMG; }
	void SetCRIT_DMG(float NewCRIT_DMG) { CRIT_DMG = NewCRIT_DMG; }

};