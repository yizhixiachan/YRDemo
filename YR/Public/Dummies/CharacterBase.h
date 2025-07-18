// Copyright © 2025 yizhixiachan

#pragma once

#include "CoreMinimal.h"
#include "Dummies/DummyBase.h"

#include "CharacterBase.generated.h"

class USpringArmComponent;
class UCameraComponent;
class AYRPlayerController;
class AEnemyBase;
class UInventoryLayout;

UCLASS()
class YR_API ACharacterBase : public ADummyBase
{
	GENERATED_BODY()
	
public:
	ACharacterBase();

	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

	//~ 开始战斗接口
	virtual void INT_ReceivePreInput(bool EnablePreInput) override;
	virtual void INT_TryNextCombo() override;
	virtual void INT_End() override;
	virtual void INT_HandleWeaponEquip(bool Equip) override;
	virtual void INT_StopMontage() override;
	//~ 结束战斗接口
public:
	/**设置武器的位置 */
	UFUNCTION(BlueprintImplementableEvent)
	void AttachWeaponToSocket(bool Equip);

public:
	//~ 开始InputAction事件
	void MoveForward(float Val);
	void MoveRight(float Val);
	void LookUp(float Val);
	void LookRight(float Val);
	void TryAttack();
	void TryLock();
	void TryOpenInventory();
	void TrySheathe();
	//~ 结束InputAction事件

	void DetectEnemy();
	void SwitchLockMode(bool IsLocking);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UCameraComponent* FollowCamera = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AYRPlayerController* PC = nullptr;

	/**被锁定的敌人对象 */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AEnemyBase* LockedEnemy = nullptr;

	/**软引用背包UI类 */
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSoftClassPtr<UUserWidget> InventoryClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UInventoryLayout* InventoryLayout;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bOpenInventory = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bOpenStore = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Anims")
	UAnimMontage* EquipAnim = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Anims")
	UAnimMontage* UnequipAnim = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Anims")
	UAnimMontage* ATKAnim = nullptr;

	// 当前连击段
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CurCombo = 0;
	// 是否开启连招判定
	bool bEnablePreInput = false;
	// 是否已输入连击
	bool bHasPreInput = false;
	
};
