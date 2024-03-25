// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TicNonPlayerCharacter.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AttributeSets/TicPlayerAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "Character/TicAIController.h"

ATicNonPlayerCharacter::ATicNonPlayerCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UTicPlayerAttributeSet>(TEXT("AttributeSet"));

	static ConstructorHelpers::FClassFinder<AAIController> AI_CONTROLLER_CLASS(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/AI/BP_TicAIController.BP_TicAIController_C'"));
	if (AI_CONTROLLER_CLASS.Succeeded())
	{
		AIControllerClass = AI_CONTROLLER_CLASS.Class;
		AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	}
}

void ATicNonPlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(ATicNonPlayerCharacter, AttributeSet);
}