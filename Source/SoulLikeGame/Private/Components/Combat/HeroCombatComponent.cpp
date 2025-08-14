// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/HeroCombatComponent.h"
#include "Items/Weapons/SoulHeroWeapon.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "SoulGameplayTags.h"

#include "SoulDebugHelper.h"

ASoulHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag)
{
  return Cast<ASoulHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

ASoulHeroWeapon* UHeroCombatComponent::GetHeroCurrentEquippedWeapon() const
{
	return Cast<ASoulHeroWeapon>(GetCharacterCurrentEquippedWeapon());
}

float UHeroCombatComponent::GetHeroCurrentEquippedWeaponDamageAtLevel(float InLevel) const
{
	return GetHeroCurrentEquippedWeapon()->HeroWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel);
}

void UHeroCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor)) return;

  OverlappedActors.AddUnique(HitActor);

  FGameplayEventData Data;
  Data.Instigator = GetOwningPawn();
  Data.Target = HitActor;

  UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
    GetOwningPawn(),
    SoulGameplayTags::Shared_Event_MeleeHit,
    Data
  );

  UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
    GetOwningPawn(),
    SoulGameplayTags::Player_Event_HitPause,
    FGameplayEventData()
  );
}

void UHeroCombatComponent::PostHitTargetActor(AActor* HitActor)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
    GetOwningPawn(),
    SoulGameplayTags::Player_Event_HitPause,
    FGameplayEventData()
  );
}