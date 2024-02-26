// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Tasks/AT_JumpAndWaitForLanding.h"
#include "GameFramework/Character.h"

UAT_JumpAndWaitForLanding::UAT_JumpAndWaitForLanding()
{

}

UAT_JumpAndWaitForLanding* UAT_JumpAndWaitForLanding::CreateTask(UGameplayAbility* OwningAbility)
{
	UAT_JumpAndWaitForLanding* NewTask = NewAbilityTask<UAT_JumpAndWaitForLanding>(OwningAbility);
	return NewTask;
}

void UAT_JumpAndWaitForLanding::Activate()
{
	Super::Activate();

	ACharacter* Character = CastChecked<ACharacter>(GetAvatarActor());
	Character->LandedDelegate.AddDynamic(this, &ThisClass::OnLandedCallback);
	Character->Jump();

	SetWaitingOnAvatar();
}

void UAT_JumpAndWaitForLanding::OnDestroy(bool bInOwnerFinished)
{
	ACharacter* Character = CastChecked<ACharacter>(GetAvatarActor());
	Character->LandedDelegate.RemoveDynamic(this, &ThisClass::OnLandedCallback);

	Super::OnDestroy(bInOwnerFinished);
}

void UAT_JumpAndWaitForLanding::OnLandedCallback(const FHitResult& HitResult)
{
	if (ShouldBroadcastAbilityTaskDelegates())	// Is Ability Active ?
	{
		OnCompleted.Broadcast();
	}
}
