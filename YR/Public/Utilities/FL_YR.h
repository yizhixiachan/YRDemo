// Copyright © 2025 yizhixiachan

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FL_YR.generated.h"

class UYRGameInstance;

UCLASS()
class YR_API UFL_YR : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**DebugHelper */
	static void Print(const FString& DebugMessage)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, DebugMessage);
		}
	}

	/**等级与最大经验值的计算公式 */
	static float FLib_GetMaxEXP(int32 Level);

	/**获取游戏实例 */
	static UYRGameInstance* Flib_GetGI(const UObject* WorldContextObject);
	
	
};
