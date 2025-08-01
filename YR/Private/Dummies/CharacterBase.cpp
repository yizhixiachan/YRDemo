// Copyright © 2025 yizhixiachan


#include "Dummies/CharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "System/YRPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/InventoryLayout.h"
#include "Dummies/EnemyBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "DrawDebugHelpers.h"
#include "System/YRPlayerState.h"
#include "System/YRGameInstance.h"
#include "Subsystem/InventorySubsystem.h"

ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	//~ 开始角色参数和摄像机初始化
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
	FollowCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	//~ 结束角色参数和摄像机初始化

}

void ACharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	PC = Cast<AYRPlayerController>(NewController);
}

void ACharacterBase::UnPossessed()
{
	Super::UnPossessed();

	PC = nullptr;
}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	AYRPlayerState* PS = GetPlayerState<AYRPlayerState>();
	DummyAttr = PS->AllCharAttributeMap[PS->CurCharIndex];
	if (DummyAttr.GetEquipmentSlots().WeaponSlot.ItemType != EItemType::IT_EMAX)
	{
		FWeaponRow WeaponRow =  UFL_YR::Flib_GetGI(GetWorld())->GetSubsystem<UInventorySubsystem>()
			->GetItemRow(DummyAttr.GetEquipmentSlots().WeaponSlot, false).WeaponRow;
		WeaponMesh->SetStaticMesh(WeaponRow.WeaponMesh.LoadSynchronous());
	}
}

void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//~ 开始绑定输入事件
	InputComponent->BindAxis("MoveForWard", this, &ACharacterBase::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ACharacterBase::MoveRight);
	InputComponent->BindAxis("LookUp", this, &ACharacterBase::LookUp);
	InputComponent->BindAxis("LookRight", this, &ACharacterBase::LookRight);
	InputComponent->BindAction("OpenInventory", IE_Pressed, this, &ACharacterBase::TryOpenInventory).bExecuteWhenPaused = true;
	InputComponent->BindAction("MMB", IE_Pressed, this, &ACharacterBase::TryLock);
	InputComponent->BindAction("Sheathe", IE_Pressed, this, &ACharacterBase::TrySheathe);
	//~ 结束绑定输入事件
}

void ACharacterBase::Tick(float DeltaTime)
{
	if (bLocking)
	{
		/**检测与敌人之间是否有障碍物 */
		FHitResult HitResult;
		FCollisionObjectQueryParams ObjectQueryParams(ECollisionChannel::ECC_WorldStatic);
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);

		bool bHit = GetWorld()->LineTraceSingleByObjectType(
			HitResult,
			GetActorLocation(),
			LockedEnemy->GetActorLocation(),
			ObjectQueryParams,
			QueryParams
		);

		if (!LockedEnemy->bDead && (LockedEnemy->GetActorLocation() - GetActorLocation()).Size() <= 2000.f && !bHit)
		{
			FVector Direction = LockedEnemy->GetActorLocation() - GetActorLocation();
			FRotator NewRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
			FRotator DeltaPCRot = FMath::RInterpTo(GetControlRotation(), NewRotation, DeltaTime, 2.0f);
			FRotator DeltaRot = FMath::RInterpTo(GetActorRotation(), NewRotation, DeltaTime, 5.0f);
			FRotator DeltaRot2D(0.0f, DeltaRot.Yaw, 0.0f);
			PC->SetControlRotation(DeltaPCRot);
			SetActorRotation(DeltaRot2D);
		}
		/**敌人死亡解除锁定 */
		/**超出距离解除锁定 */
		/**存在障碍物解除锁定 */
		else
		{
			SwitchLockMode(false);
		}
	}

}

void ACharacterBase::INT_ReceivePreInput(bool EnablePreInput)
{
	bEnablePreInput = EnablePreInput;
}

void ACharacterBase::INT_TryNextCombo()
{

}

void ACharacterBase::INT_End()
{
	bUseUpperBodySlot = false;
}

void ACharacterBase::INT_HandleWeaponEquip(bool Equip)
{
	bEquipping = Equip;
	AttachWeaponToSocket(Equip);
}

void ACharacterBase::INT_StopMontage()
{
}

void ACharacterBase::MoveForward(float Val)
{
	if (PC && Val != 0.0f)
	{
		const FRotator GroundRotation(0.f, PC->GetControlRotation().Yaw, 0.f);
		const FVector ForwardDir = FRotationMatrix(GroundRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(ForwardDir, Val);
	}
}

void ACharacterBase::MoveRight(float Val)
{
	if (PC && Val != 0.0f)
	{
		const FRotator GroundRotation(0.f, PC->GetControlRotation().Yaw, 0.f);
		const FVector RightDir = FRotationMatrix(GroundRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(RightDir, Val);
	}
}

void ACharacterBase::LookUp(float Val)
{

	if (PC && Val != 0.0f && !bLocking)
	{
		AddControllerPitchInput(Val);
	}
}

void ACharacterBase::LookRight(float Val)
{
	if (PC && Val != 0.0f && !bLocking)
	{
		AddControllerYawInput(Val);
	}
}

void ACharacterBase::TryAttack()
{
	if (!PC) return;
}

void ACharacterBase::TryLock()
{
	if (!PC) return;
	if (!WeaponMesh->GetStaticMesh()) return;

	if (!bLocking)
	{

		DetectEnemy();
		SwitchLockMode(true);
	}
	else
	{
		SwitchLockMode(false);
	}
}

void ACharacterBase::TryOpenInventory()
{
	if (!PC) return;
	if (bOpenStore) return;

	if (InventoryLayout && InventoryLayout->IsInViewport())
	{
		InventoryLayout->UpdateInventory();
		InventoryLayout->RemoveFromParent();
		InventoryLayout = nullptr;

		PC->bShowMouseCursor = false;
		FInputModeGameOnly InputMode;
		PC->SetInputMode(InputMode);
		bOpenInventory = false;

		/**更新武器模型 */
		AYRPlayerState* PS = GetPlayerState<AYRPlayerState>();
		DummyAttr = PS->AllCharAttributeMap[PS->CurCharIndex];
		if (DummyAttr.GetEquipmentSlots().WeaponSlot.ItemType != EItemType::IT_EMAX)
		{
			FWeaponRow WeaponRow = UFL_YR::Flib_GetGI(GetWorld())->GetSubsystem<UInventorySubsystem>()
				->GetItemRow(DummyAttr.GetEquipmentSlots().WeaponSlot, false).WeaponRow;
			WeaponMesh->SetStaticMesh(WeaponRow.WeaponMesh.LoadSynchronous());
		}
		else
		{
			WeaponMesh->SetStaticMesh(nullptr);
		}

		/**恢复游戏 */ 
		UGameplayStatics::SetGamePaused(GetWorld(), false);
	}
	else
	{
		/**软引用同步加载 */ 
		TSubclassOf<UUserWidget> WidgetClass = InventoryClass.LoadSynchronous();
		if (!WidgetClass) return;

		InventoryLayout = CreateWidget<UInventoryLayout>(PC, WidgetClass);
		if (InventoryLayout)
		{
			InventoryLayout->AddToViewport();

			PC->bShowMouseCursor = true;
			FInputModeGameAndUI InputMode;
			InputMode.SetWidgetToFocus(InventoryLayout->TakeWidget());
			PC->SetInputMode(InputMode);
			
			InventoryLayout->UpdateInventory();
			bOpenInventory = true;
			/**暂停游戏 */ 
			UGameplayStatics::SetGamePaused(GetWorld(), true);
		}
	}
}

void ACharacterBase::TrySheathe()
{
	if (!PC || !bEquipping || bLocking || bAiming) return;

	PlayAnimMontage(UnequipAnim, 1.0f);
}

void ACharacterBase::DetectEnemy()
{
	TArray<FVector> DetectedEnemyVecArr;
	TArray<AActor*> DetectedEnemyArr;

	TArray<FOverlapResult> OverlapResults;
	FRotator Rot2D(0.f, PC->GetControlRotation().Yaw, 0.f);
	FVector Pos = GetActorLocation() + Rot2D.Vector() * 750.f;
	FVector Extent = FVector(750.f, 750.f, 200.0f);
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	bool Overlap = GetWorld()->OverlapMultiByObjectType(
		OverlapResults,
		Pos,
		FQuat::Identity,
		ECollisionChannel::ECC_Pawn,
		FCollisionShape::MakeBox(Extent),
		QueryParams
	);
	//DrawDebugBox(GetWorld(), Pos, Extent, FColor::Red, false, 2.f);
	if (Overlap)
	{
		for (const auto& OverlapResult : OverlapResults)
		{
			AActor* DetectedActor = OverlapResult.GetActor();
			if (DetectedActor && DetectedActor->IsA(AEnemyBase::StaticClass()))
			{
				/**检测与敌人之间是否有障碍物 */
				FHitResult HitResult;
				FCollisionObjectQueryParams ObjectQueryParams(ECollisionChannel::ECC_WorldStatic);

				bool bHit = GetWorld()->LineTraceSingleByObjectType(
					HitResult,
					GetActorLocation(),
					DetectedActor->GetActorLocation(),
					ObjectQueryParams,
					QueryParams
				);
				//DrawDebugLine(GetWorld(), GetActorLocation(), DetectedActor->GetActorLocation(), FColor::Red, false, 2.f);
				if (!bHit)
				{
					DetectedEnemyVecArr.Add(DetectedActor->GetActorLocation() - GetActorLocation());
					DetectedEnemyArr.Add(DetectedActor);
				}
			}
		}

		/**选出最靠近视野中心的目标 */
		float BestDotProduct = 0.5f;
		AActor* BestEnemy = nullptr;
		for (size_t Index = 0; Index < DetectedEnemyVecArr.Num(); ++Index)
		{
			FVector Dir = FVector::ZeroVector;
			float Distance = 0.f;
			DetectedEnemyVecArr[Index].ToDirectionAndLength(Dir, Distance);
			float DotProduct = FVector::DotProduct(PC->GetControlRotation().Vector(), Dir);
			if (DotProduct > BestDotProduct) 
			{
				BestDotProduct = DotProduct;
				BestEnemy = DetectedEnemyArr[Index];
			}
		}
		LockedEnemy = Cast<AEnemyBase>(BestEnemy);
	}

}

void ACharacterBase::SwitchLockMode(bool IsLocking)
{
	if (IsLocking)
	{
		if (!LockedEnemy) return;

		if (!bEquipping)
		{
			bUseUpperBodySlot = true;
			PlayAnimMontage(EquipAnim, 1.0f);
		}
	}

	bLocking = IsLocking;
	GetCharacterMovement()->bOrientRotationToMovement = !IsLocking;
	if (bAiming && !bLocking) GetCharacterMovement()->bOrientRotationToMovement = false;
	bWalking = IsLocking;
	GetCharacterMovement()->MaxWalkSpeed = IsLocking ? 200.0f : 500.0f;
	LockedEnemy->LockIcon->SetHiddenInGame(!bLocking);
	if (!bLocking) LockedEnemy = nullptr;
}
