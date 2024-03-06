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

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PostAttributeBaseChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) const override;

	ATTRIBUTE_ACCESSORS(UTicPlayerAttributeSet, MaxHP);
	ATTRIBUTE_ACCESSORS(UTicPlayerAttributeSet, HP);
	ATTRIBUTE_ACCESSORS(UTicPlayerAttributeSet, MaxAttackRange);
	ATTRIBUTE_ACCESSORS(UTicPlayerAttributeSet, AttackRange);
	ATTRIBUTE_ACCESSORS(UTicPlayerAttributeSet, MaxAttackRate);
	ATTRIBUTE_ACCESSORS(UTicPlayerAttributeSet, AttackRate);
	ATTRIBUTE_ACCESSORS(UTicPlayerAttributeSet, MaxAttackRadius);
	ATTRIBUTE_ACCESSORS(UTicPlayerAttributeSet, AttackRadius);

	UFUNCTION()
	virtual void OnRep_MaxHP(const FGameplayAttributeData& OldMaxHP);

	UFUNCTION()
	virtual void OnRep_HP(const FGameplayAttributeData& OldHP);

	UFUNCTION()
	virtual void OnRep_MaxAttackRange(const FGameplayAttributeData& OldMaxAttackRange);

	UFUNCTION()
	virtual void OnRep_AttackRange(const FGameplayAttributeData& OldAttackRange);

	UFUNCTION()
	virtual void OnRep_MaxAttackRate(const FGameplayAttributeData& OldMaxAttackRate);

	UFUNCTION()
	virtual void OnRep_AttackRate(const FGameplayAttributeData& OldAttackRate);

	UFUNCTION()
	virtual void OnRep_MaxAttackRadius(const FGameplayAttributeData& OldMaxAttackRadius);

	UFUNCTION()
	virtual void OnRep_AttackRadius(const FGameplayAttributeData& OldAttackRadius);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Property", ReplicatedUsing = OnRep_MaxHP, Meta = (AllowPrivateAccess = "True"))
	FGameplayAttributeData MaxHP;

	UPROPERTY(BlueprintReadOnly, Category = "Property", ReplicatedUsing = OnRep_HP, Meta = (AllowPrivateAccess = "True"))
	FGameplayAttributeData HP;

	UPROPERTY(BlueprintReadOnly, Category = "Property", ReplicatedUsing = OnRep_MaxAttackRange, Meta = (AllowPrivateAccess = "True"))
	FGameplayAttributeData MaxAttackRange;

	UPROPERTY(BlueprintReadOnly, Category = "Property", ReplicatedUsing = OnRep_AttackRange, Meta = (AllowPrivateAccess = "True"))
	FGameplayAttributeData AttackRange;

	UPROPERTY(BlueprintReadOnly, Category = "Property", ReplicatedUsing = OnRep_MaxAttackRate, Meta = (AllowPrivateAccess = "True"))
	FGameplayAttributeData MaxAttackRate;

	UPROPERTY(BlueprintReadOnly, Category = "Property", ReplicatedUsing = OnRep_AttackRate, Meta = (AllowPrivateAccess = "True"))
	FGameplayAttributeData AttackRate;

	UPROPERTY(BlueprintReadOnly, Category = "Property", ReplicatedUsing = OnRep_MaxAttackRadius, Meta = (AllowPrivateAccess = "True"))
	FGameplayAttributeData MaxAttackRadius;

	UPROPERTY(BlueprintReadOnly, Category = "Property", ReplicatedUsing = OnRep_AttackRadius, Meta = (AllowPrivateAccess = "True"))
	FGameplayAttributeData AttackRadius;
};
