// Copyright © 2025 yizhixiachan


#include "Animations/AN_HandleWeaponEquip.h"
#include "Interfaces/CombatInterface.h"

void UAN_HandleWeaponEquip::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(MeshComp->GetOwner());
	if (CombatInterface)
	{
		CombatInterface->INT_HandleWeaponEquip(bEquip);
	}
}
