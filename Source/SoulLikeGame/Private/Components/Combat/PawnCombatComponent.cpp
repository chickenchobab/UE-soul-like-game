// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/PawnCombatComponent.h"
#include "Items/Weapons/SoulWeaponBase.h"

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

  const FString WeaponString = FString::Printf(TEXT("A Weapon named : %s has been registered using the tag %s"),
    *InWeapon->GetName(),
    *InWeaponTag.ToString()
  );
  Debug::Print(WeaponString);
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