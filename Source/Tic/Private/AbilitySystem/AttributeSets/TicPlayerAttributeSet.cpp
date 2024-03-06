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

	DOREPLIFETIME_CONDITION_NOTIFY(UTicPlayerAttributeSet, MaxHP, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTicPlayerAttributeSet, HP, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTicPlayerAttributeSet, MaxAttackRange, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTicPlayerAttributeSet, AttackRange, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTicPlayerAttributeSet, MaxAttackRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTicPlayerAttributeSet, AttackRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTicPlayerAttributeSet, MaxAttackRadius, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTicPlayerAttributeSet, AttackRadius, COND_None, REPNOTIFY_Always);
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

void UTicPlayerAttributeSet::OnRep_MaxHP(const FGameplayAttributeData& OldMaxHP)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTicPlayerAttributeSet, MaxHP, OldMaxHP);
}

void UTicPlayerAttributeSet::OnRep_HP(const FGameplayAttributeData& OldHP)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTicPlayerAttributeSet, HP, OldHP);
}

void UTicPlayerAttributeSet::OnRep_MaxAttackRange(const FGameplayAttributeData& OldMaxAttackRange)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTicPlayerAttributeSet, MaxAttackRange, OldMaxAttackRange);
}

void UTicPlayerAttributeSet::OnRep_AttackRange(const FGameplayAttributeData& OldAttackRange)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTicPlayerAttributeSet, AttackRange, OldAttackRange);
}

void UTicPlayerAttributeSet::OnRep_MaxAttackRate(const FGameplayAttributeData& OldMaxAttackRate)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTicPlayerAttributeSet, MaxAttackRate, OldMaxAttackRate);
}

void UTicPlayerAttributeSet::OnRep_AttackRate(const FGameplayAttributeData& OldAttackRate)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTicPlayerAttributeSet, AttackRate, OldAttackRate);
}

void UTicPlayerAttributeSet::OnRep_MaxAttackRadius(const FGameplayAttributeData& OldMaxAttackRadius)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTicPlayerAttributeSet, MaxAttackRadius, OldMaxAttackRadius);
}

void UTicPlayerAttributeSet::OnRep_AttackRadius(const FGameplayAttributeData& OldAttackRadius)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTicPlayerAttributeSet, AttackRadius, OldAttackRadius);
	//static FProperty* ThisProperty = FindFieldChecked<FProperty>(UTicPlayerAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UTicPlayerAttributeSet, AttackRadius));
	//GetOwningAbilitySystemComponentChecked()->SetBaseAttributeValueFromReplication(FGameplayAttribute(ThisProperty), AttackRadius, OldAttackRadius);
	//GetOwningAbilitySystemComponentChecked()->SetBaseAttributeValueFromReplication(FGameplayAttribute(ThisProperty), AttackRadius, OldAttackRadius);
}
