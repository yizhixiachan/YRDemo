// Copyright © 2025 yizhixiachan

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ESData/DummyData.h"
#include "Interfaces/CombatInterface.h"

#include "DummyBase.generated.h"

UCLASS()
class YR_API ADummyBase : public ACharacter, public ICombatInterface
{
	GENERATED_BODY()

public:
	ADummyBase();

protected:
	virtual void BeginPlay() override;

	//~ 开始战斗接口
	virtual void INT_Begin() override;
	virtual void INT_ReceivePreInput(bool EnablePreInput) override;
	virtual void INT_TryNextCombo() override;
	virtual void INT_End() override;
	virtual void INT_HandleWeaponEquip(bool Equip) override;
	virtual void INT_StopMontage() override;
	//~ 结束战斗接口
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FDummyAttributes DummyAttr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* WeaponMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bDead = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bWalking = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bEquipping = false;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bLocking = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bUseUpperBodySlot = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bAiming = false;
};
