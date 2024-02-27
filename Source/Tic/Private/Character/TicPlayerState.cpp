// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TicPlayerState.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AttributeSets/TicPlayerAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "Tic.h"

ATicPlayerState::ATicPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->SetIsReplicated(true);
	}
	AttributeSet = CreateDefaultSubobject<UTicPlayerAttributeSet>(TEXT("AttributeSet"));
}

UAbilitySystemComponent* ATicPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ATicPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(ATicPlayerState, AttributeSet);
}

//void ATicPlayerState::OnRep_AttributeSet()
//{
//	UE_LOG(WJTest, Log, TEXT("%.0f, %d"), AttributeSet->GetHP(), GetNetMode());
//}
