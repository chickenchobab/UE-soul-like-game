// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/SoulGameplayAbility.h"
#include "SoulEnemyGameplayAbility.generated.h"

class ASoulEnemyCharacter;
class UEnemyCombatComponent;

/**
 * 
 */
UCLASS()
class SOULLIKEGAME_API USoulEnemyGameplayAbility : public USoulGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Ability")
	ASoulEnemyCharacter* GetEnemyCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

private:
	TWeakObjectPtr<ASoulEnemyCharacter> CachedEnemyCharacter;
	
};
