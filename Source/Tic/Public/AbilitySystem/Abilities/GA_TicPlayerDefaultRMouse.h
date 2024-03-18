// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_TicPlayerDefaultRMouse.generated.h"

/**
 * 
 */
UCLASS()
class TIC_API UGA_TicPlayerDefaultRMouse : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGA_TicPlayerDefaultRMouse();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	UFUNCTION()
	void AbilityEnded();

	UFUNCTION()
	void InputPress(float TimeWaited);
};
