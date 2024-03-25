// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TicGameplayTag.h"

TicGameplayTag::TicGameplayTag()
{
}

TicGameplayTag::~TicGameplayTag()
{
}

FGameplayTag TicGameplayTag::Character_State_IsJumping()
{
	return FGameplayTag::RequestGameplayTag(TEXT("Character.State.IsJumping"));
}

FGameplayTag TicGameplayTag::Character_State_IsAttacking()
{
	return FGameplayTag::RequestGameplayTag(TEXT("Character.State.IsAttacking"));
}

FGameplayTag TicGameplayTag::Event_Attack_HitCheck()
{
	return FGameplayTag::RequestGameplayTag(TEXT("Event.Attack.HitCheck"));
}

FGameplayTag TicGameplayTag::GameplayCue_Character_AttackHit()
{
	return FGameplayTag::RequestGameplayTag(TEXT("GameplayCue.Character.AttackHit"));
}

FGameplayTag TicGameplayTag::Data_Damage()
{
	return FGameplayTag::RequestGameplayTag(TEXT("Data.Damage"));
}
