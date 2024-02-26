// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/AnimNotify_AttackHitCheck.h"
#include "AbilitySystemBlueprintLibrary.h"

FString UAnimNotify_AttackHitCheck::GetNotifyName_Implementation() const
{
	return TEXT("AttackHitCheck");
}

void UAnimNotify_AttackHitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	AActor* MeshOwner = MeshComp->GetOwner();
	check(MeshOwner);

	FGameplayEventData Payload;
	if (TriggerTag.IsValid())
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshOwner, TriggerTag, Payload);
	}
}
