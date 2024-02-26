// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/TicBaseCharacter.h"
#include "TicNonPlayerCharacter.generated.h"

class UAbilitySystemComponent;
class UTicPlayerAttributeSet;

/**
 * 
 */
UCLASS()
class TIC_API ATicNonPlayerCharacter : public ATicBaseCharacter
{
	GENERATED_BODY()
	
public:
	ATicNonPlayerCharacter();

protected:
	UPROPERTY(VisibleAnywhere, Category = "GAS")
	TObjectPtr<UTicPlayerAttributeSet> AttributeSet;
};
