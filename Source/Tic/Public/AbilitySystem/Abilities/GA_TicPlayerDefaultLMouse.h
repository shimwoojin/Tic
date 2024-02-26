// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_TicPlayerDefaultLMouse.generated.h"

/**
 * GA_TicPlayerDefaultLMouse
 */
UCLASS()
class TIC_API UGA_TicPlayerDefaultLMouse : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGA_TicPlayerDefaultLMouse();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility) override;

	UFUNCTION()
	void OnCompleted();

	UFUNCTION()
	void OnInterrupted();

	UFUNCTION()
	void OnCancelled();
};
