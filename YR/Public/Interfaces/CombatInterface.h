// Copyright © 2025 yizhixiachan

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

UINTERFACE(MinimalAPI)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

class YR_API ICombatInterface
{
	GENERATED_BODY()

public:
	virtual void INT_Begin() = 0;
	virtual void INT_ReceivePreInput(bool EnablePreInput) = 0;
	virtual void INT_TryNextCombo() = 0;
	virtual void INT_End() = 0;
	virtual void INT_HandleWeaponEquip(bool Equip) = 0;
	virtual void INT_StopMontage() = 0;
};
