// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpDataBase.generated.h"

class USoulGameplayAbility;
class USoulAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class SOULLIKEGAME_API UDataAsset_StartUpDataBase : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(USoulAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
	
protected:
	void GrantAbilities(const TArray<TSubclassOf<USoulGameplayAbility>>& InAbilitiesToGive, USoulAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<USoulGameplayAbility>> ActivateOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<USoulGameplayAbility>> ReactiveAbilities;
};
