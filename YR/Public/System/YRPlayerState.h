// Copyright © 2025 yizhixiachan

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ESData/DummyData.h"
#include "YRPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class YR_API AYRPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	/**已拥有角色的属性数据 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TMap<int32, FDummyAttributes> AllCharAttributeMap;

	/**上阵的角色队伍 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<int32> BattleTeam;

	/**当前使用角色的队伍编号 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 CurCharIndex = 1;
	
};
