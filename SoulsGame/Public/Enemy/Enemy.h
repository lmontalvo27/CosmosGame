// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Characters/CharacterTypes.h"
#include "Enemy.generated.h"


 
class UHealthBarComponent;
class UPawnSensingComponent;

UCLASS()
class SOULSGAME_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	AEnemy(); 
	
	//Actor
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Destroyed() override;

	// <IHitInterface
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;

protected:
	virtual void BeginPlay() override;
	
	//Base Character
	virtual void Die() override;
	void SpawnSoul();
	virtual void Attack() override;
	virtual bool CanAttack() override;
	virtual void AttackEnd() override;
	virtual void HandleDamage(float DamageAmount) override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		EEnemyState EnemyState = EEnemyState::EES_Patrolling;
private:
	// AI Behavior
	void CheckPatrolTarget();
	void CheckCombatTarget();
	void HideHealthBar();
	void ShowHealthBar();
	void LoseInterest();
	void StartPatrolling();
	void ChaseTarget();
	bool IsOutsideCombatRadius();
	bool IsOutsideAttackRadius();
	bool IsInsideAttackRadius();
	bool IsChasing();
	bool IsAttacking();
	bool IsDead();
	bool IsEngaged();
	void ClearPatrolTimer();
	void PatrolTimerFinished();
	void StartAttackTimer();
	void ClearAttackTimer();
	bool InTargetRange(AActor* Target, double Radius);
	void MoveToTarget(AActor* Target);
	AActor* ChoosePatrolTarget();
	void SpawnDefaultWeapon();
	void InitializeEnemy();

	UFUNCTION()
		void PawnSeen(APawn* SeenPawn); // called back for OnPawnSeen in UPawnSensingComponent

	UPROPERTY(VisibleAnywhere)
		UHealthBarComponent* HealthBarWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		UPawnSensingComponent* PawnSensing;

	UPROPERTY(EditAnywhere, Category = Combat)
		TSubclassOf<class AWeapon> WeaponClass;

	/**
		Animation Montages
	**/

	//UPROPERTY()
	//AActor* CombatTarget;

	UPROPERTY(EditAnywhere, Category = Combat)
		double CombatRadius = 1000.f;

	UPROPERTY(EditAnywhere, Category = Combat)
		double AttackRadius = 150.f;

	UPROPERTY(EditAnywhere, Category = Combat)
		double AcceptanceRadius = 50.f;

	UPROPERTY()
		class AAIController* EnemyController;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
		AActor* PatrolTarget;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
		TArray<AActor*> PatrolTargets;

	UPROPERTY(EditAnywhere)
		double PatrolRadius = 200.f;

	FTimerHandle PatrolTimer;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
		float PatrolWaitMin = 5.f;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
		float PatrolWaitMax = 10.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float PatrollingSpeed = 125.f;
	
	FTimerHandle AttackTimer;

	UPROPERTY(EditAnywhere, Category = Combat)
	float AttackMin = 0.5f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float AttackMax = 1.f;

	UPROPERTY(EditAnywhere, Category = Combat)
		float ChasingSpeed = 300.f;

	UPROPERTY(EditAnywhere, Category = Combat)
		float DeathLifeSpan = 15.f;

	UPROPERTY(EditAnywhere, Category = Combat)
		TSubclassOf<class ASoul> SoulClass;
};
