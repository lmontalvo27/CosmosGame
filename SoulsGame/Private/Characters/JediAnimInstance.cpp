// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/JediAnimInstance.h"
#include "Characters/JediCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UJediAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	JediCharacter = Cast<AJediCharacter>(TryGetPawnOwner());
	if (JediCharacter)
	{
		JediCharacterMovement = JediCharacter->GetCharacterMovement();
	}
}

void UJediAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (JediCharacterMovement)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(JediCharacterMovement->Velocity);
		IsFalling = JediCharacterMovement->IsFalling();
		CharacterState = JediCharacter->GetCharacterState();
		ActionState = JediCharacter->GetActionState();
		DeathPose = JediCharacter->GetDeathPose();
	}
}
