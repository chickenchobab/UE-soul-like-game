// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/PawnCombatComponent.h"
#include "Items/Weapons/SoulWeaponBase.h"
#include "Components/BoxComponent.h"

#include "SoulDebugHelper.h"

void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTag, ASoulWeaponBase* InWeapon, bool bRegisterAsEquippedWeapon)
{
  checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTag), TEXT("A weapon named %s has already been added as carried weapon"), *InWeaponTag.ToString());
  check(InWeapon);

  CharacterCarriedWeaponMap.Emplace(InWeaponTag, InWeapon);

  InWeapon->OnWeaponHitTarget.BindUObject(this, &ThisClass::OnHitTargetActor);
  InWeapon->PostWeaponHitTarget.BindUObject(this, &ThisClass::PostHitTargetActor);
  
  if (bRegisterAsEquippedWeapon)
  {
    CurrentEquippedWeaponTag = InWeaponTag;
  }
}

ASoulWeaponBase* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	if (CharacterCarriedWeaponMap.Contains(InWeaponTag))
  {
    if(ASoulWeaponBase* const* FoundWeapon = CharacterCarriedWeaponMap.Find(InWeaponTag))
    {
      return *FoundWeapon;
    }
  }

  return nullptr;
}

ASoulWeaponBase* UPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid()) return nullptr;
  return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}


void UPawnCombatComponent::ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
  if (ToggleDamageType == EToggleDamageType::CurrentEquippedWeapon)
  {
    ToggleCurrentEquippedWeaponCollision(bShouldEnable);
  }
  else
  {
    ToggleBodyCollisionBoxCollision(bShouldEnable, ToggleDamageType);
  }
}

void UPawnCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	
}

void UPawnCombatComponent::PostHitTargetActor(AActor* HitActor)
{
	
}


void UPawnCombatComponent::ToggleCurrentEquippedWeaponCollision(bool bShouldEnable)
{
  ASoulWeaponBase* WeaponToToggle = GetCharacterCurrentEquippedWeapon();

  check(WeaponToToggle);

  if (bShouldEnable)
  {
    WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
  }
  else
  {
    WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    OverlappedActors.Empty();
  }
}


void UPawnCombatComponent::ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{

}

