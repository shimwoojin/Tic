// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimInstance/TicCharacterAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UTicCharacterAnimInstance::UTicCharacterAnimInstance()
{
	Character = nullptr;
	MoveComp = nullptr;
	GroundSpeed = 0.0f;
	Velocity = FVector::ZeroVector;
	bShouldMove = false;
	bIsFalling = false;
	bIsCrouching = false;
}

void UTicCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (GetOwningActor())
	{
		Character = Cast<ACharacter>(GetOwningActor());

		if (Character)
		{
			MoveComp = Character->GetCharacterMovement();
		}
	}
}

void UTicCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (IsValid(Character) && IsValid(MoveComp))
	{
		Velocity = MoveComp->Velocity;
		GroundSpeed = Velocity.Size2D();
		bShouldMove = GroundSpeed > 3.0f ? true : false;
		bIsFalling = MoveComp->IsFalling();
		bIsCrouching = MoveComp->IsCrouching();
	}
}
