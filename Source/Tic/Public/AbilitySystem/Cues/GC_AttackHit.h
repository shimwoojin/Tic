// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Static.h"
#include "GC_AttackHit.generated.h"

/**
 * 
 */
UCLASS()
class TIC_API UGC_AttackHit : public UGameplayCueNotify_Static
{
	GENERATED_BODY()
	
public:
	UGC_AttackHit();

	bool OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const;

protected:
	UPROPERTY(EditAnywhere, Category = "Particle")
	TObjectPtr<class UParticleSystem> HitParticle;
};
