// Copyright © 2025 yizhixiachan

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ESData/DummyData.h"
#include "InventoryLayout.generated.h"

class AYRPlayerState;
 
UCLASS()
class YR_API UInventoryLayout : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "YRPlayerState")
	bool GetAllCharAttr(TMap<int32, FDummyAttributes>& OutAllCharAttr) const;

	UFUNCTION(BlueprintCallable, Category = "YRPlayerState")
	void GetBattleTeam(TArray<int32>& OutBattleTeam);

	UFUNCTION(BlueprintCallable, Category = "YRPlayerState")
	int32 GetCurCharIndex();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateInventory();
};
