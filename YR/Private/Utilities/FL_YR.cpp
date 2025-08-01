// Copyright © 2025 yizhixiachan


#include "Utilities/FL_YR.h"
#include "Kismet/GameplayStatics.h"
#include "System/YRGameInstance.h"

float UFL_YR::FLib_GetMaxEXP(int32 Level)
{
	// 基础公式：MaxExp = Base * Level^Exponent
	const float Base = 100.0f;
	const float Exponent = 1.8f;  // 控制曲线陡峭度

	// 分段调整系数
	float adjustment = 1.0f;

	if (Level <= 5) {
		// 1-5级：平缓增长 (新手友好)
		adjustment = 0.7f;
	}
	else if (Level <= 20) {
		// 6-20级：正常增长
		adjustment = 1.0f;
	}
	else if (Level <= 50) {
		// 21-50级：加速增长
		adjustment = 1.3f;
	}
	else {
		// 50+级：指数级增长 (高等级挑战)
		adjustment = 1.8f + (Level - 50) * 0.05f;
	}

	// 最终计算（添加基础偏移保证最低经验）
	float MaxEXP = FMath::RoundToInt(adjustment * Base * FMath::Pow(Level, Exponent)) + 50;

	return FMath::Max(100.0f, MaxEXP);  // 保证最低100经验
}

UYRGameInstance* UFL_YR::Flib_GetGI(const UObject* WorldContextObject)
{
	if (!WorldContextObject) return nullptr;
	UWorld* World = WorldContextObject->GetWorld();
	if (!World) return nullptr;

	return Cast<UYRGameInstance>(World->GetGameInstance());
}
