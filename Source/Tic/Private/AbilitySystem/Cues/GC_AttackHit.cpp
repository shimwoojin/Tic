// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Cues/GC_AttackHit.h"
#include "Kismet/GameplayStatics.h"
#include "Tic.h"

UGC_AttackHit::UGC_AttackHit()
{
}

bool UGC_AttackHit::OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const
{
	const FHitResult* HitResult = Parameters.EffectContext.GetHitResult();

	if (HitResult && HitParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, HitResult->Location);
	}

	return true;
}
