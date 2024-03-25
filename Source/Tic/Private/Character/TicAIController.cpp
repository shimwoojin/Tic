// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TicAIController.h"
#include "Tic.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ATicAIController::ATicAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT_ASSET(TEXT("/Script/AIModule.BehaviorTree'/Game/Blueprint/AI/BT_AITest.BT_AITest'"));
	if (BT_ASSET.Succeeded())
	{
		BTAsset = BT_ASSET.Object;
	}

	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
}

void ATicAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunAI(); 
	InitPerception();
}

void ATicAIController::RunAI()
{
	UE_LOG(TicAI, Log, TEXT("%s : RunBehaviorTree"), ANSI_TO_TCHAR(__FUNCTION__));
	bool bResult = RunBehaviorTree(BTAsset);
	ensure(bResult);

	if (Blackboard)
	{
		Blackboard->SetValueAsVector("Location1", FVector(500.0f, 0.0f, 0.0f));
		Blackboard->SetValueAsVector("Location2", FVector(-500.0f, 0.0f, 0.0f));
	}
}

void ATicAIController::StopAI()
{
}

void ATicAIController::InitPerception()
{
	check(PerceptionComponent);

	UAISenseConfig_Sight* SightConfig = NewObject<UAISenseConfig_Sight>(this, TEXT("Sight"));
	if (SightConfig)
	{
		SightConfig->SightRadius = 2000.0f;
		SightConfig->LoseSightRadius = 2500.0f;
		SightConfig->PeripheralVisionAngleDegrees = 80.0f;

		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		PerceptionComponent->ConfigureSense(*SightConfig);
	}

	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ThisClass::TargetPerceptionUpdatedCallback);
}

void ATicAIController::TargetPerceptionUpdatedCallback(AActor* Actor, FAIStimulus Stimulus)
{
	if (::IsValid(Actor) && Stimulus.WasSuccessfullySensed())
	{
		UE_LOG(TicAI, Log, TEXT("%s Detected Successful : %s"), *Actor->GetName(), *Stimulus.StimulusLocation.ToString());
	}
}
