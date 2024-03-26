// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Tasks/AT_Crouch.h"
#include "GameFramework/Character.h"

UAT_Crouch::UAT_Crouch()
{
}

UAT_Crouch* UAT_Crouch::CreateTask(UGameplayAbility* OwningAbility)
{
	UAT_Crouch* NewTask = NewAbilityTask<UAT_Crouch>(OwningAbility);
	return NewTask;
}

void UAT_Crouch::Activate()
{
	Super::Activate();

	ACharacter* Character = CastChecked<ACharacter>(GetAvatarActor());
	Character->Crouch();

	SetWaitingOnAvatar();
}

void UAT_Crouch::EndTask()
{
	ACharacter* Character = CastChecked<ACharacter>(GetAvatarActor());
	Character->UnCrouch();
}

void UAT_Crouch::OnDestroy(bool bInOwnerFinished)
{
}
