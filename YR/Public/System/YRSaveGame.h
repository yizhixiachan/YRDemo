// Copyright © 2025 yizhixiachan

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ESData/DummyData.h"
#include "YRSaveGame.generated.h"


UCLASS()
class YR_API UYRSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
    //~ 开始角色数据
    UPROPERTY()
    TMap<int32, FDummyAttributes> SavedAllCharAttr;
    UPROPERTY()
    TArray<int32> SavedBattleTeam;
    UPROPERTY()
    int32 SavedCurCharIndex;
    UPROPERTY()
    FTransform SavedCurCharTrans;
    //~ 结束角色数据

    //~ 开始背包数据
    UPROPERTY()
    TMap<FItemUID, int32> SavedAllItemMap;
    UPROPERTY()
    TMap<int32, FWeaponInstance> SavedAllWeaponMap;
    UPROPERTY()
    TMap<int32, FGearInstance> SavedAllGearMap;
    UPROPERTY()
    int32 SavedMoney;
    UPROPERTY()
    int32 SavedInventorySize;
    UPROPERTY()
    int32 SavedNextWeaponID;
    UPROPERTY()
    int32 SavedNextGearID;
    //~ 结束背包数据
};
