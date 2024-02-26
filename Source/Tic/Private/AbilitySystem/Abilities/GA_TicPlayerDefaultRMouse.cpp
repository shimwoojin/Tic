// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GA_TicPlayerDefaultRMouse.h"
#include "Tic.h"
#include "Abilities/GameplayAbilityTypes.h"

UGA_TicPlayerDefaultRMouse::UGA_TicPlayerDefaultRMouse()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_TicPlayerDefaultRMouse::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AActor* OwnerActor = ActorInfo->OwnerActor.Get();
	AActor* AvatarActor = ActorInfo->AvatarActor.Get();
	check(OwnerActor && AvatarActor);

	if (Handle.IsValid())
	{
		UE_LOG(TicActivateAbility, Log, TEXT("AbilitySpecHandle : %s, OwnerActor : %s, AvatarActor : %s"), *Handle.ToString(), *OwnerActor->GetName(), *AvatarActor->GetName());
	}

	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}