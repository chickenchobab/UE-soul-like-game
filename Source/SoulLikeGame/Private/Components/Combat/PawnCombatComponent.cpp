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
    ASoulWeaponBase* WeaponToToggle = GetCharacterCurrentEquippedWeapon();

    check(WeaponToToggle)

    if (bShouldEnable)
    {
      WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
      Debug::Print(WeaponToToggle->GetName() + TEXT(" collision enabled"), FColor::Green);
    }
    else
    {
      WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
      Debug::Print(WeaponToToggle->GetName() + TEXT(" collision disabled"), FColor::Red);
    }

  }
}
