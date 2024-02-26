// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TicBaseCharacter.h"
#include "AbilitySystemComponent.h"

ATicBaseCharacter::ATicBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;


}

UAbilitySystemComponent* ATicBaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ATicBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATicBaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ATicBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATicBaseCharacter::InitStartAbilities()
{
	check(AbilitySystemComponent);

	for (const auto& StartAbility : StartAbilities)
	{
		FGameplayAbilitySpec Spec(StartAbility);
		AbilitySystemComponent->GiveAbility(Spec);
	}
}

