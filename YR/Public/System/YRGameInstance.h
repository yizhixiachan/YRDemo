// Copyright © 2025 yizhixiachan

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "YRGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class YR_API UYRGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void OnStart() override;

	UFUNCTION(BlueprintImplementableEvent)
	void InitInventory();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bNewGame = true;
};
