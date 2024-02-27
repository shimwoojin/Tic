// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GA_TicPlayerDefaultLMouse.h"
#include "Tic.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystem/TicGameplayTag.h"

UGA_TicPlayerDefaultLMouse::UGA_TicPlayerDefaultLMouse()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;
	ActivationOwnedTags.AddTag(TicGameplayTag::Character_State_IsAttacking());
}

void UGA_TicPlayerDefaultLMouse::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AActor* OwnerActor = ActorInfo->OwnerActor.Get();
	AActor* AvatarActor = ActorInfo->AvatarActor.Get();
	check(OwnerActor && AvatarActor);

	if (Handle.IsValid())
	{
		UE_LOG(TicActivateAbility, Log, TEXT("AbilitySpecHandle : %s, OwnerActor : %s, AvatarActor : %s"), *Handle.ToString(), *OwnerActor->GetName(), *AvatarActor->GetName());
	}

	//TODO
	static UAnimMontage* MontageToPlay = LoadObject<UAnimMontage>(this, TEXT("/Script/Engine.AnimMontage'/Game/Assets/Characters/Mannequins/Animations/Actions/Mma_Kick_Anim_Montage.Mma_Kick_Anim_Montage'"));
	if (MontageToPlay)
	{
		ACharacter* Character = CastChecked<ACharacter>(AvatarActor);
		Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

		UAbilityTask_PlayMontageAndWait* MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("MontagePlay"), MontageToPlay);
		MontageTask->OnCompleted.AddDynamic(this, &UGA_TicPlayerDefaultLMouse::OnCompleted);
		MontageTask->OnBlendOut.AddDynamic(this, &UGA_TicPlayerDefaultLMouse::OnBlendOut);
		MontageTask->OnInterrupted.AddDynamic(this, &UGA_TicPlayerDefaultLMouse::OnInterrupted);
		MontageTask->OnCancelled.AddDynamic(this, &UGA_TicPlayerDefaultLMouse::OnCancelled);
		MontageTask->ReadyForActivation();
	}
	else
	{
		UE_LOG(TicAssetNotFound, Warning, TEXT("Not Found MontageToPlay"));
	}
}

void UGA_TicPlayerDefaultLMouse::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	ACharacter* Character = CastChecked<ACharacter>(ActorInfo->AvatarActor.Get());
	Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_TicPlayerDefaultLMouse::OnCompleted()
{
	bool bReplicateEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_TicPlayerDefaultLMouse::OnBlendOut()
{
	bool bReplicateEndAbility = true;
	bool bWasCancelled = false;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_TicPlayerDefaultLMouse::OnInterrupted()
{
	bool bReplicateEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGA_TicPlayerDefaultLMouse::OnCancelled()
{
	bool bReplicateEndAbility = true;
	bool bWasCancelled = true;
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}
