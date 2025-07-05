// Copyright © 2025 yizhixiachan

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstanceProxy.h"
#include "ESData/DummyAnimData.h"

class ADummyBase;

struct YR_API FDummyAnimProxy : public FAnimInstanceProxy
{
public:
    FDummyAnimProxy(UAnimInstance* Instance = nullptr)
        : FAnimInstanceProxy(Instance)
    {
    }

    // 使用游戏线程更新数据
    void SetGameData_GameThread(ADummyBase* InDummy, FVector InVelocity,  FRotator InActorRot, FRotator InControlRot,
        bool HasAccele, bool Walking, bool Equipping, bool Locking, bool UseUpperBodySlot, bool Aiming )
    {
        FScopeLock Lock(&GameThreadDataLock);
        Dummy = InDummy;
        AnimData.Velocity = InVelocity;
        AnimData.ActorRotator = InActorRot;
        AnimData.ControlRotator = InControlRot;
        AnimData.bHasAcceleration = HasAccele;
        AnimData.bWalking = Walking;
        AnimData.bEquipping = Equipping;
        AnimData.bLocking = Locking;
        AnimData.bUseUpperBodySlot = UseUpperBodySlot;
        AnimData.bAiming = Aiming;
    }

    ADummyBase* GetDummy() const
    {
        FScopeLock Lock(&GameThreadDataLock);
        return Dummy;
    }

   const FDummyAnimData& GetAnimData() const
    {
        FScopeLock Lock(&GameThreadDataLock);
        return AnimData;
    }


private:
    // 非递归锁
    mutable FCriticalSection GameThreadDataLock;

    ADummyBase* Dummy;
    FDummyAnimData AnimData;
};