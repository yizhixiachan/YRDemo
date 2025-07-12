// Copyright © 2025 yizhixiachan

#pragma once

#include "CoreMinimal.h"
#include "DummyAnimData.generated.h"

/**供动画蓝图使用的数据 */
USTRUCT(BlueprintType)
struct YR_API FDummyAnimData
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData")
	FVector Velocity = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData")
	FRotator ActorRotator = FRotator::ZeroRotator;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData")
	FRotator ControlRotator = FRotator::ZeroRotator;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData")
	bool bHasAcceleration = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData")
	bool bWalking = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData")
	bool bEquipping = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData")
	bool bLocking = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData")
	bool bUseUpperBodySlot = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData")
	bool bAiming = false;

};