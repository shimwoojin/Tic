// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GA_TicPlayerDefaultRMouse.h"
#include "Tic.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Abilities/Tasks/AbilityTask_MoveToLocation.h"
#include "Abilities/Tasks/AbilityTask_WaitInputPress.h"

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

	FVector TargetLocation = AvatarActor->GetActorLocation() + FVector(500.0f, 0.0f, 0.0f);
	UAbilityTask_MoveToLocation* MoveTask = UAbilityTask_MoveToLocation::MoveToLocation(this, TEXT("MoveToLocation"), TargetLocation, 3.0f, nullptr, nullptr);
	
	UAbilityTask_WaitInputPress* WaitInputPressTask = UAbilityTask_WaitInputPress::WaitInputPress(this);
	WaitInputPressTask->OnPress.AddDynamic(this, &ThisClass::InputPress);
	WaitInputPressTask->ReadyForActivation();

	if (::IsValid(MoveTask))
	{
		MoveTask->OnTargetLocationReached.AddDynamic(this, &ThisClass::AbilityEnded);
		MoveTask->ReadyForActivation();
	}
	else
	{
		AbilityEnded();
	}
}

void UGA_TicPlayerDefaultRMouse::AbilityEnded()
{
	bool bReplicatedEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicatedEndAbility, bWasCancelled);
}

void UGA_TicPlayerDefaultRMouse::InputPress(float TimeWaited)
{
	UE_LOG(TicActivateAbility, Log, TEXT("Input Pressed : %f"), TimeWaited);
}
