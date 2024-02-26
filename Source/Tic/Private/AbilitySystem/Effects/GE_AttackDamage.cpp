// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Effects/GE_AttackDamage.h"
#include "AbilitySystem/AttributeSets/TicPlayerAttributeSet.h"

UGE_AttackDamage::UGE_AttackDamage()
{
	DurationPolicy = EGameplayEffectDurationType::Instant;
	FGameplayModifierInfo HealthModifier;
	HealthModifier.Attribute = UTicPlayerAttributeSet::GetHPAttribute();
	HealthModifier.ModifierOp = EGameplayModOp::Additive;

	FScalableFloat DamageAmount(-30.0f);
	FGameplayEffectModifierMagnitude ModMagnitude(DamageAmount);
	HealthModifier.ModifierMagnitude = ModMagnitude;

	Modifiers.Add(HealthModifier);
}
