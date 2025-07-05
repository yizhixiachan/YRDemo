// Copyright © 2025 yizhixiachan

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryLayout.generated.h"

/**
 * 
 */
UCLASS()
class YR_API UInventoryLayout : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void InitializeInventoryLayout();
	
};
