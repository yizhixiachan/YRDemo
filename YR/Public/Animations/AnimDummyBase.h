// Copyright © 2025 yizhixiachan

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Animations/DummyAnimProxy.h"
#include "ESData/DummyAnimData.h"
#include "AnimDummyBase.generated.h"

UCLASS()
class YR_API UAnimDummyBase : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override;
	virtual void DestroyAnimInstanceProxy(FAnimInstanceProxy* InProxy) override;

private:
	FDummyAnimProxy& GetDummyProxy();

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AnimData")
    ADummyBase* Dummy;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimData")
	FDummyAnimData AnimData;

};
