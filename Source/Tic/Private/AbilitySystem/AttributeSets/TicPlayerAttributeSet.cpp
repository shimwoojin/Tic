// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSets/TicPlayerAttributeSet.h"
#include "Tic.h"
#include "Net/UnrealNetwork.h"

UTicPlayerAttributeSet::UTicPlayerAttributeSet()
	: MaxHP(100),
	HP(100),
	MaxAttackRange(100.0f),
	AttackRange(100.0f),
	MaxAttackRate(30.0f),
	AttackRate(30.0f),
	MaxAttackRadius(50.0f),
	AttackRadius(50.0f)
{

}

void UTicPlayerAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UTicPlayerAttributeSet, MaxHP);
	DOREPLIFETIME(UTicPlayerAttributeSet, HP);
	DOREPLIFETIME(UTicPlayerAttributeSet, MaxAttackRange);
	DOREPLIFETIME(UTicPlayerAttributeSet, AttackRange);
	DOREPLIFETIME(UTicPlayerAttributeSet, MaxAttackRate);
	DOREPLIFETIME(UTicPlayerAttributeSet, AttackRate);
	DOREPLIFETIME(UTicPlayerAttributeSet, MaxAttackRadius);
	DOREPLIFETIME(UTicPlayerAttributeSet, AttackRadius);
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
