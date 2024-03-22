// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TicAIController.h"
#include "Tic.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

ATicAIController::ATicAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT_ASSET(TEXT("/Script/AIModule.BehaviorTree'/Game/Blueprint/AI/BT_AITest.BT_AITest'"));
	if (BT_ASSET.Succeeded())
	{
		BTAsset = BT_ASSET.Object;
	}
}

void ATicAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunAI();
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
