// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/SoulGameplayAbility.h"
#include "SoulHeroGameplayAbility.generated.h"

class ASoulHeroCharacter;
class ASoulHeroController;
class UHeroCombatComponent;

/**
 * 
 */
UCLASS()
class SOULLIKEGAME_API USoulHeroGameplayAbility : public USoulGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "SoulAbility")
	ASoulHeroCharacter* GetHeroCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "SoulAbility")
	ASoulHeroController* GetHeroControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "SoulAbility")
	UHeroCombatComponent* GetHeroCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "SoulAbility")
	FGameplayEffectSpecHandle MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount);
	
private:
	TWeakObjectPtr<ASoulHeroCharacter> CachedHeroCharacter;
	TWeakObjectPtr<ASoulHeroController> CachedHeroController;
};
