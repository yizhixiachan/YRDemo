// Copyright © 2025 yizhixiachan


#include "Dummies/DummyBase.h"

ADummyBase::ADummyBase()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon"));
	WeaponMesh->SetupAttachment(GetMesh());
}

void ADummyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADummyBase::INT_Begin()
{
}

void ADummyBase::INT_ReceivePreInput(bool EnablePreInput)
{
}

void ADummyBase::INT_TryNextCombo()
{
}

void ADummyBase::INT_End()
{
}

void ADummyBase::INT_HandleWeaponEquip(bool Equip)
{
}

void ADummyBase::INT_StopMontage()
{
}
