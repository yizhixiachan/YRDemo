// Copyright © 2025 yizhixiachan


#include "Dummies/EnemyBase.h"
#include "Components/WidgetComponent.h"

AEnemyBase::AEnemyBase()
{
	LockIcon = CreateDefaultSubobject<UWidgetComponent>("Lock Icon");
	LockIcon->SetHiddenInGame(true);
	LockIcon->SetupAttachment(RootComponent);
}
