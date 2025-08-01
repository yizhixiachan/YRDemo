// Copyright © 2025 yizhixiachan


#include "Animations/AN_End.h"
#include "Interfaces/CombatInterface.h"

void UAN_End::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(MeshComp->GetOwner());
	if (CombatInterface)
	{
		CombatInterface->INT_End();
	}

}
