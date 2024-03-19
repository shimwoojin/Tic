// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TicAIController.h"
#include "Tic.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"

ATicAIController::ATicAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT_ASSET(TEXT("/Script/AIModule.BlackboardData'/Game/Blueprint/AI/BB_AITest.BB_AITest'"));
	if (BT_ASSET.Succeeded())
	{
		BTAsset = BT_ASSET.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BB_ASSET(TEXT("/Script/AIModule.BlackboardData'/Game/Blueprint/AI/BB_AITest.BB_AITest'"));
	if (BB_ASSET.Succeeded())
	{
		BBAsset = BB_ASSET.Object;
	}
}

void ATicAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunAI();
}

void ATicAIController::RunAI()
{
	UBlackboardComponent* BlackboardComponent;
	if (UseBlackboard(BBAsset, BlackboardComponent))
	{
		RunBehaviorTree(BTAsset);
	}
}

void ATicAIController::StopAI()
{
}
