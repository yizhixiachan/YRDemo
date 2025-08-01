// Copyright © 2025 yizhixiachan


#include "Subsystem/YRSaveGameSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystem/InventorySubsystem.h"
#include "System/YRPlayerState.h"
#include "System/YRSaveGame.h"
#include "System/YRGameInstance.h"
#include "GameFramework/Character.h"

bool UYRSaveGameSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
    Super::ShouldCreateSubsystem(Outer);
    return true;
}

void UYRSaveGameSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    CurrentSaveSlot = "DefaultSaveSlot";

    if (UGameplayStatics::DoesSaveGameExist(CurrentSaveSlot, 0))
    {
        CurrentSaveGame = Cast<UYRSaveGame>(UGameplayStatics::LoadGameFromSlot(CurrentSaveSlot, 0));
    }
}

void UYRSaveGameSubsystem::Deinitialize()
{
    CurrentSaveGame = nullptr;

    Super::Deinitialize();
}

void UYRSaveGameSubsystem::SaveGame()
{
    CollectSaveData();
    UGameplayStatics::SaveGameToSlot(CurrentSaveGame, CurrentSaveSlot, 0);
}

bool UYRSaveGameSubsystem::LoadInventory()
{
    UInventorySubsystem* InventorySubsystem = UFL_YR::Flib_GetGI(GetWorld())->GetSubsystem<UInventorySubsystem>();
    if (!InventorySubsystem || !InventorySubsystem->GetInventory()) return false;

    InventorySubsystem->InitializeInventoryData(
        CurrentSaveGame->SavedAllItemMap,
        CurrentSaveGame->SavedAllWeaponMap,
        CurrentSaveGame->SavedAllGearMap,
        CurrentSaveGame->SavedInventorySize,
        CurrentSaveGame->SavedMoney,
        CurrentSaveGame->SavedNextWeaponID,
        CurrentSaveGame->SavedNextGearID);

    return true;

}

bool UYRSaveGameSubsystem::LoadPlayerState()
{
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    AYRPlayerState* PlayerState = PC ? PC->GetPlayerState<AYRPlayerState>() : nullptr;
    if (!PlayerState) return false;

    PlayerState->AllCharAttributeMap = CurrentSaveGame->SavedAllCharAttr;
    PlayerState->BattleTeam = CurrentSaveGame->SavedBattleTeam;
    PlayerState->CurCharIndex = CurrentSaveGame->SavedCurCharIndex;

    return true;

}

bool UYRSaveGameSubsystem::LoadPostion()
{
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    ACharacter* Character = PC->GetCharacter();
    if (!Character) return false;

    Character->SetActorTransform(CurrentSaveGame->SavedCurCharTrans);
    return true;
}

void UYRSaveGameSubsystem::SetActiveSaveSlot(const FString& SlotName)
{
    CurrentSaveSlot = SlotName;
}

void UYRSaveGameSubsystem::CollectSaveData()
{
    UInventorySubsystem* InventorySubsystem = UFL_YR::Flib_GetGI(GetWorld())->GetSubsystem<UInventorySubsystem>();
    if (!InventorySubsystem || !InventorySubsystem->GetInventory()) return;

    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    AYRPlayerState* PlayerState = PC ? PC->GetPlayerState<AYRPlayerState>() : nullptr;
    if (!PlayerState) return;

    ACharacter* Character = PC->GetCharacter();
    if (!Character) return;

    /**收集数据 */
    CurrentSaveGame->SavedAllItemMap = InventorySubsystem->GetAllItemMap();
    CurrentSaveGame->SavedAllWeaponMap = InventorySubsystem->GetAllWeaponMap();
    CurrentSaveGame->SavedAllGearMap = InventorySubsystem->GetAllGearMap();
    CurrentSaveGame->SavedMoney = InventorySubsystem->GetMoney();
    CurrentSaveGame->SavedInventorySize = InventorySubsystem->GetInventorySize();
    CurrentSaveGame->SavedNextWeaponID = InventorySubsystem->GetNextWeaponID();
    CurrentSaveGame->SavedNextGearID = InventorySubsystem->GetNextGearID();

    CurrentSaveGame->SavedAllCharAttr = PlayerState->AllCharAttributeMap;
    CurrentSaveGame->SavedBattleTeam = PlayerState->BattleTeam;
    CurrentSaveGame->SavedCurCharIndex = PlayerState->CurCharIndex;

    CurrentSaveGame->SavedCurCharTrans = Character->GetActorTransform();

}
