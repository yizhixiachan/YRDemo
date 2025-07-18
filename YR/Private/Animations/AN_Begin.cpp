// Copyright © 2025 yizhixiachan


#include "Animations/AN_Begin.h"
#include "Interfaces/CombatInterface.h"

void UAN_Begin::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(MeshComp->GetOwner());
	if (CombatInterface)
	{
		CombatInterface->INT_Begin();
	}

}
