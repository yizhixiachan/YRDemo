// Copyright © 2025 yizhixiachan


#include "Animations/ANS_PreInput.h"
#include "Interfaces/CombatInterface.h"

void UANS_PreInput::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(MeshComp->GetOwner());

	if (CombatInterface)
	{
		CombatInterface->INT_ReceivePreInput(true);
	}
}

void UANS_PreInput::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(MeshComp->GetOwner());

	if (CombatInterface)
	{
		CombatInterface->INT_ReceivePreInput(false);
	}
}
