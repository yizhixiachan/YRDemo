// Copyright © 2025 yizhixiachan


#include "Animations/AN_TryNextCombo.h"
#include "Interfaces/CombatInterface.h"

void UAN_TryNextCombo::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(MeshComp->GetOwner());
	if (CombatInterface)
	{
		CombatInterface->INT_TryNextCombo();
	}
}
