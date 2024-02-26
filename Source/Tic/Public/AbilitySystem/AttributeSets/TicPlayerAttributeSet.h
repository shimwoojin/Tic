// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "TicPlayerAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * TicPlayerAttributeSet
 */
UCLASS()
class TIC_API UTicPlayerAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UTicPlayerAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PostAttributeBaseChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) const override;

	ATTRIBUTE_ACCESSORS(UTicPlayerAttributeSet, TestData);
	ATTRIBUTE_ACCESSORS(UTicPlayerAttributeSet, MaxHP);
	ATTRIBUTE_ACCESSORS(UTicPlayerAttributeSet, HP);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Property", Meta = (AllowPrivateAccess = "True"))
	FGameplayAttributeData TestData;

	UPROPERTY(BlueprintReadOnly, Category = "Property", Meta = (AllowPrivateAccess = "True"))
	FGameplayAttributeData MaxHP;

	UPROPERTY(BlueprintReadOnly, Category = "Property", Meta = (AllowPrivateAccess = "True"))
	FGameplayAttributeData HP;
};
