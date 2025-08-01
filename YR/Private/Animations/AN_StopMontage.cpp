// Copyright © 2025 yizhixiachan


#include "Animations/AN_StopMontage.h"
#include "Interfaces/CombatInterface.h"

void UAN_StopMontage::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(MeshComp->GetOwner());
	if (CombatInterface)
	{
		CombatInterface->INT_StopMontage();
	}
}
