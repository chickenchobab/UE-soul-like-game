// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/SoulHeroGameplayAbility.h"
#include "Characters/SoulHeroCharacter.h"
#include "Controllers/SoulHeroController.h"

ASoulHeroCharacter* USoulHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
  if (!CachedHeroCharacter.IsValid())
  {
    CachedHeroCharacter = Cast<ASoulHeroCharacter>(CurrentActorInfo->AvatarActor);
  }
  return CachedHeroCharacter.IsValid() ? CachedHeroCharacter.Get() : nullptr;
}


ASoulHeroController* USoulHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
  if (!CachedHeroController.IsValid())
  {
    CachedHeroController = Cast<ASoulHeroController>(CurrentActorInfo->PlayerController);
  }
  return CachedHeroController.IsValid() ? CachedHeroController.Get() : nullptr;
}


UHeroCombatComponent* USoulHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
  return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}
