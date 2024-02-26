// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * 
 */
class TIC_API TicGameplayTag
{
public:
	TicGameplayTag();
	~TicGameplayTag();

	//Character State
	static FGameplayTag Character_State_IsJumping();
	static FGameplayTag Character_State_IsAttacking();

	//Event
	static FGameplayTag Event_Attack_HitCheck();

	//GameplayCue
	static FGameplayTag GameplayCue_Character_AttackHit();
};
