// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GA_Jump.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "GameFramework/Character.h"
#include "AbilitySystem/Tasks/AT_JumpAndWaitForLanding.h"
#include "AbilitySystem/TicGameplayTag.h"
#include "Tic.h"

UGA_Jump::UGA_Jump()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	ActivationOwnedTags.AddTag(TicGameplayTag::Character_State_IsJumping());
}

bool UGA_Jump::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
	bool bResult = Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
	if (!bResult)
	{
		return false;
	}

	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
	return (Character && Character->CanJump());
}

void UGA_Jump::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AActor* OwnerActor = ActorInfo->OwnerActor.Get();
	AActor* AvatarActor = ActorInfo->AvatarActor.Get();
	check(OwnerActor && AvatarActor);

	if (Handle.IsValid())
	{
		UE_LOG(TicActivateAbility, Log, TEXT("AbilitySpecHandle : %s, OwnerActor : %s, AvatarActor : %s"), *Handle.ToString(), *OwnerActor->GetName(), *AvatarActor->GetName());
	}

	//CreateTask
	UAT_JumpAndWaitForLanding* JumpAndWaitForLandingTask = UAT_JumpAndWaitForLanding::CreateTask(this);
	JumpAndWaitForLandingTask->OnCompleted.AddDynamic(this, &ThisClass::OnLandedCallback);
	JumpAndWaitForLandingTask->ReadyForActivation();
}

void UGA_Jump::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor.Get());
	Character->StopJumping();
}

void UGA_Jump::OnLandedCallback()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

