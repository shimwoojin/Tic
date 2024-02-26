// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSets/TicPlayerAttributeSet.h"
#include "Tic.h"

UTicPlayerAttributeSet::UTicPlayerAttributeSet()
	: TestData(0),
	MaxHP(100),
	HP(100)
{

}

void UTicPlayerAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	if (Attribute == GetHPAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHP());
	}
}

void UTicPlayerAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	UE_LOG(TicAttributeChange, Log, TEXT("%s OldValue : %f, NewValue : %f"), *Attribute.AttributeName, OldValue, NewValue);
}

void UTicPlayerAttributeSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute == GetHPAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHP());
	}
}

void UTicPlayerAttributeSet::PostAttributeBaseChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) const
{
	UE_LOG(TicAttributeBaseChange, Log, TEXT("%s OldValue : %f, NewValue : %f"), *Attribute.AttributeName, OldValue, NewValue);
}
