// Copyright © 2025 yizhixiachan

#pragma once

#include "CoreMinimal.h"
#include "Dummies/DummyBase.h"
#include "EnemyBase.generated.h"

class UWidgetComponent;
class AFloatingIndicator;

UCLASS()
class YR_API AEnemyBase : public ADummyBase
{
	GENERATED_BODY()
	
public:
	AEnemyBase();



public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Presets")
	UWidgetComponent* LockIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Presets")
	UWidgetComponent* HeadBar;

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Presets")
	TSubclassOf<AFloatingIndicator> FloatingIndicatorClass;*/
};
