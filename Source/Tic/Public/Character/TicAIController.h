// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TicAIController.generated.h"

/**
 * 
 */
UCLASS()
class TIC_API ATicAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ATicAIController();

	virtual void OnPossess(APawn* InPawn) override;

	void RunAI();
	void StopAI();

private:
	UPROPERTY()
	class UBehaviorTree* BTAsset;

};
