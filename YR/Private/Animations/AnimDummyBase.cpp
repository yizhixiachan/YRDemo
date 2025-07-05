// Copyright © 2025 yizhixiachan


#include "Animations/AnimDummyBase.h"
#include "Dummies/DummyBase.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAnimDummyBase::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    ADummyBase* LocalDummy = Cast<ADummyBase>(TryGetPawnOwner());
    if (!LocalDummy) return;

    FVector Velocity = LocalDummy->GetVelocity();
    FRotator ActorRot = LocalDummy->GetActorRotation();
    FRotator ControlRot = LocalDummy->GetControlRotation();
    bool HasAccele = !LocalDummy->GetCharacterMovement()->GetCurrentAcceleration().IsNearlyZero();
    bool Walking = LocalDummy->bWalking;
    bool Equipping = LocalDummy->bEquipping;
    bool Locking = LocalDummy->bLocking;
    bool UseUpperBodySlot = LocalDummy->bUseUpperBodySlot;
    bool Aiming = LocalDummy->bAiming;

    // 同步到 Proxy
    GetDummyProxy().SetGameData_GameThread(LocalDummy, Velocity, ActorRot, ControlRot, 
        HasAccele, Walking, Equipping, Locking, UseUpperBodySlot, Aiming);

    // 同步到 AnimInstance
    Dummy = GetDummyProxy().GetDummy();
    AnimData = GetDummyProxy().GetAnimData();
}

FAnimInstanceProxy* UAnimDummyBase::CreateAnimInstanceProxy()
{
	return new FDummyAnimProxy(this);
}

void UAnimDummyBase::DestroyAnimInstanceProxy(FAnimInstanceProxy* InProxy)
{
	delete InProxy;
}

FDummyAnimProxy& UAnimDummyBase::GetDummyProxy()
{
	return GetProxyOnGameThread<FDummyAnimProxy>();
}
