// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/SoulWeaponBase.h"
#include "SoulTypes/SoulStructTypes.h"
#include "SoulHeroWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SOULLIKEGAME_API ASoulHeroWeapon : public ASoulWeaponBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
	FSoulHeroWeaponData HeroWeaponData;
};
