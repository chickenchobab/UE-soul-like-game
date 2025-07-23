// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystem/SoulAbilitySystemComponent.h"
#include "SoulAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class SOULLIKEGAME_API USoulAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	USoulAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(USoulAttributeSet, CurrentHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(USoulAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Range")
	FGameplayAttributeData CurrentRange;
	ATTRIBUTE_ACCESSORS(USoulAttributeSet, CurrentRange)

	UPROPERTY(BlueprintReadOnly, Category = "Range")
	FGameplayAttributeData MaxRange;
	ATTRIBUTE_ACCESSORS(USoulAttributeSet, MaxRange)

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(USoulAttributeSet, AttackPower)

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(USoulAttributeSet, DefensePower)
};
