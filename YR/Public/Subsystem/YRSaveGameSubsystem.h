// Copyright © 2025 yizhixiachan

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ESData/DummyData.h"
#include "YRSaveGameSubsystem.generated.h"


class UYRSaveGame;

UCLASS()
class YR_API UYRSaveGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
    virtual bool ShouldCreateSubsystem(UObject* Outer) const;
    virtual void Initialize(FSubsystemCollectionBase& Collection);
    virtual void Deinitialize();


    // 保存游戏
    UFUNCTION(BlueprintCallable)
    void SaveGame();

    // 加载游戏
    UFUNCTION(BlueprintCallable)
    bool LoadInventory();

    UFUNCTION(BlueprintCallable)
    bool LoadPlayerState();

    UFUNCTION(BlueprintCallable)
    bool LoadPostion();

    UFUNCTION(BlueprintCallable)
    void SetActiveSaveSlot(const FString& SlotName);

private:
    // 收集所有需要保存的数据
    void CollectSaveData();


    // 当前存档槽位
    FString CurrentSaveSlot;

    // 存档数据缓存
    UPROPERTY()
    UYRSaveGame* CurrentSaveGame;

};
