// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GA_DefaultKick.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Tic.h"

UGA_DefaultKick::UGA_DefaultKick()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_DefaultKick::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	//UAnimMontage* MontageToPlay = FindObject<UAnimMontage>(this, TEXT("/Script/Engine.AnimMontage'/Game/Assets/Characters/Mannequins/Animations/Actions/Mma_Kick_Anim_Montage.Mma_Kick_Anim_Montage'"));
	//if (MontageToPlay)
	//{
	//	UAbilityTask_PlayMontageAndWait* MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, GetFName(), MontageToPlay);
	//	MontageTask->OnCompleted.AddDynamic(this, &UGA_DefaultKick::OnCompleted);
	//	MontageTask->OnInterrupted.AddDynamic(this, &UGA_DefaultKick::OnInterrupted);
	//	MontageTask->Activate();
	//}
	//else
	//{
	//	UE_LOG(AssetNotFound, Warning, TEXT("Not Found MontageToPlay"));
	//}
}

void UGA_DefaultKick::OnCompleted()
{
	//bool bReplicateEndAbility = false;
	//bool bWasCancelled = false;
	//EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_DefaultKick::OnInterrupted()
{
	//bool bReplicateEndAbility = false;
	//bool bWasCancelled = true;
	//EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}
