// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "DataAsset_EnemyStartUpData.generated.h"

class USoulEnemyGameplayAbility;

/**
 * 
 */
UCLASS()
class SOULLIKEGAME_API UDataAsset_EnemyStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(USoulAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray < TSubclassOf < USoulEnemyGameplayAbility > > EnemyCombatAbilities;
};
