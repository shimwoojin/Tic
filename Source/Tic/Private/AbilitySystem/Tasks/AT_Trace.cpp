// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Tasks/AT_Trace.h"
#include "AbilitySystem/TargetActors/TA_Trace.h"
#include "AbilitySystemComponent.h"

UAT_Trace* UAT_Trace::CreateTask(UGameplayAbility* OwningAbility, TSubclassOf<ATA_Trace> InTargetActorClass)
{
	UAT_Trace* NewTask = NewAbilityTask<UAT_Trace>(OwningAbility, TEXT("AT_Trace"));
	NewTask->TargetActorClass = InTargetActorClass;
	return NewTask;
}

void UAT_Trace::Activate()
{
	Super::Activate();

	SpawnAndInitializeTargetActor();
	FinalizeTargetActor();
}

void UAT_Trace::OnDestroy(bool bInOwnerFinished)
{
	if (SpawnedTargetActor)
	{
		SpawnedTargetActor->Destroy();
	}

	Super::OnDestroy(bInOwnerFinished);
}

void UAT_Trace::SpawnAndInitializeTargetActor()
{
	SpawnedTargetActor = Cast<ATA_Trace>(Ability->GetWorld()->SpawnActorDeferred<AGameplayAbilityTargetActor>(TargetActorClass, FTransform::Identity, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn));
	if (SpawnedTargetActor)
	{
		SpawnedTargetActor->SetShowDebug(true);
		SpawnedTargetActor->TargetDataReadyDelegate.AddUObject(this, &UAT_Trace::OnTargetDataReadyCallback);
	}
}

void UAT_Trace::FinalizeTargetActor()
{
	UAbilitySystemComponent* ASC = AbilitySystemComponent.Get();
	if (ASC)
	{
		const FTransform SpawnTransform = ASC->GetAvatarActor()->GetTransform();
		SpawnedTargetActor->FinishSpawning(SpawnTransform);

		ASC->SpawnedTargetActors.Push(SpawnedTargetActor);
		SpawnedTargetActor->StartTargeting(Ability);
		SpawnedTargetActor->ConfirmTargeting();
	}
}

void UAT_Trace::OnTargetDataReadyCallback(const FGameplayAbilityTargetDataHandle& DataHandle)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnCompleted.Broadcast(DataHandle);
	}

	EndTask();
}
