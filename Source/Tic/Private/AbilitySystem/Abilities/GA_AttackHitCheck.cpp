// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GA_AttackHitCheck.h"
#include "Tic.h"
#include "AbilitySystem/TicGameplayTag.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/Tasks/AT_Trace.h"
#include "AbilitySystem/TargetActors/TA_Trace.h"
#include "AbilitySystemComponent.h"

UGA_AttackHitCheck::UGA_AttackHitCheck()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	//ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateYes;
	NetExecutionPolicy;
	NetSecurityPolicy;
	FAbilityTriggerData AbilityTriggerData;
	AbilityTriggerData.TriggerTag = TicGameplayTag::Event_Attack_HitCheck();
	AbilityTriggers.Add(AbilityTriggerData);
}

void UGA_AttackHitCheck::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UAT_Trace* TraceTask = UAT_Trace::CreateTask(this, ATA_Trace::StaticClass());
	TraceTask->OnCompleted.AddDynamic(this, &UGA_AttackHitCheck::OnTraceResultCallback);
	TraceTask->ReadyForActivation();
}

void UGA_AttackHitCheck::OnTraceResultCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	if (UAbilitySystemBlueprintLibrary::TargetDataHasHitResult(TargetDataHandle, 0))
	{
		FHitResult HitResult = UAbilitySystemBlueprintLibrary::GetHitResultFromTargetData(TargetDataHandle, 0);
		UE_LOG(TicCommonLog, Log, TEXT("Target %s Detected"), *(HitResult.GetActor()->GetName()));

		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(HitResult.GetActor());
		if (!TargetASC)
		{
			UE_LOG(TicCommonLog, Log, TEXT("TargetASC Not Found!!"));
			return;
		}

		FGameplayEffectSpecHandle AttackDamageSpecHandle = MakeOutgoingGameplayEffectSpec(AttackDamageEffectClass);
		if (AttackDamageSpecHandle.IsValid())
		{
			ApplyGameplayEffectSpecToTarget(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, AttackDamageSpecHandle, TargetDataHandle);

			FGameplayEffectContextHandle EffectContextHandle = UAbilitySystemBlueprintLibrary::GetEffectContext(AttackDamageSpecHandle);
			EffectContextHandle.AddHitResult(HitResult);
			FGameplayCueParameters CueParams(EffectContextHandle);
			TargetASC->ExecuteGameplayCue(TicGameplayTag::GameplayCue_Character_AttackHit(), CueParams);
		}

		FGameplayEffectSpecHandle RangeBuffSpecHandle = MakeOutgoingGameplayEffectSpec(AttackRangeBuffEffectClass);
		if (RangeBuffSpecHandle.IsValid())
		{
			ApplyGameplayEffectSpecToOwner(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, RangeBuffSpecHandle);
		}
	}

	bool bReplicateEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}
