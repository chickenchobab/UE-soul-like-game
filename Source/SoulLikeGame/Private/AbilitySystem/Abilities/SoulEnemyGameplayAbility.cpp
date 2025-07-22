// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/SoulEnemyGameplayAbility.h"
#include "Characters/SoulEnemyCharacter.h"

ASoulEnemyCharacter* USoulEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (!CachedEnemyCharacter.IsValid())
  {
    CachedEnemyCharacter = Cast<ASoulEnemyCharacter>(CurrentActorInfo->AvatarActor);
  }
  return CachedEnemyCharacter.IsValid() ? CachedEnemyCharacter.Get() : nullptr;
}

UEnemyCombatComponent* USoulEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}
