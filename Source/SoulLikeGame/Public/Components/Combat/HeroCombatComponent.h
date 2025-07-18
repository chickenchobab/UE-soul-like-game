// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "HeroCombatComponent.generated.h"

class ASoulHeroWeapon;

/**
 * 
 */
UCLASS()
class SOULLIKEGAME_API UHeroCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Combat")
	ASoulHeroWeapon* GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag);
};
