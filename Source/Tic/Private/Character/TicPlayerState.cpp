// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TicPlayerState.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AttributeSets/TicPlayerAttributeSet.h"

ATicPlayerState::ATicPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UTicPlayerAttributeSet>(TEXT("AttributeSet"));
}

UAbilitySystemComponent* ATicPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

