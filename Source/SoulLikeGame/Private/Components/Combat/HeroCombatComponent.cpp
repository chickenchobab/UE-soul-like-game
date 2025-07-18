// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/HeroCombatComponent.h"
#include "Items/Weapons/SoulHeroWeapon.h"

ASoulHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag)
{
  return Cast<ASoulHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}
