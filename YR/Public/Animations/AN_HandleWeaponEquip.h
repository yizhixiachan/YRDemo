// Copyright © 2025 yizhixiachan

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_HandleWeaponEquip.generated.h"

/**
 * 
 */
UCLASS()
class YR_API UAN_HandleWeaponEquip : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite);
	bool bEquip = true;
};

