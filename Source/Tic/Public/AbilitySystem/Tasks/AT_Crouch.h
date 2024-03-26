// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AT_Crouch.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCrouchSignature);

/**
 * 
 */
UCLASS()
class TIC_API UAT_Crouch : public UAbilityTask
{
	GENERATED_BODY()

public:
	UAT_Crouch();

public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "Crouch",
		HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UAT_Crouch* CreateTask(UGameplayAbility* OwningAbility);

	virtual void Activate() override;
	void EndTask();
	virtual void OnDestroy(bool bInOwnerFinished) override;
};
