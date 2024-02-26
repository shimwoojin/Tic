// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_DefaultKick.generated.h"

/**
 * GA_DefaultKick
 */
UCLASS()
class TIC_API UGA_DefaultKick : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGA_DefaultKick();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION()
	void OnCompleted();

	UFUNCTION()
	void OnInterrupted();
};
