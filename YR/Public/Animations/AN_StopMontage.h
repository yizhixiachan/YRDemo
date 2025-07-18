// Copyright © 2025 yizhixiachan

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_StopMontage.generated.h"

/**
 * 
 */
UCLASS()
class YR_API UAN_StopMontage : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
