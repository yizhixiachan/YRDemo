// Copyright © 2025 yizhixiachan


#include "UI/InventoryLayout.h"
#include "System/YRPlayerController.h"
#include "System/YRPlayerState.h"

bool UInventoryLayout::GetAllCharAttr(TMap<int32, FDummyAttributes>& OutAllCharAttr) const
{
    if (const AYRPlayerController* PC = GetOwningPlayer<AYRPlayerController>())
    {
        AYRPlayerState* PS = PC->GetPlayerState<AYRPlayerState>();
        if (PS)
        {
            OutAllCharAttr = PS->AllCharAttributeMap;
            return true;
        }
    }
    return false;
}

void UInventoryLayout::GetBattleTeam(TArray<int32>& OutBattleTeam)
{
    if (const AYRPlayerController* PC = GetOwningPlayer<AYRPlayerController>())
    {
        AYRPlayerState* PS = PC->GetPlayerState<AYRPlayerState>();
        if (PS)
        {
            OutBattleTeam = PS->BattleTeam;
        }
    }
}

int32 UInventoryLayout::GetCurCharIndex()
{
    if (const AYRPlayerController* PC = GetOwningPlayer<AYRPlayerController>())
    {
        AYRPlayerState* PS = PC->GetPlayerState<AYRPlayerState>();
        if (PS)
        {
            return PS->CurCharIndex;
        }
    }
    return -1;
}
