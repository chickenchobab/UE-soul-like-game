// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/DataAsset_EnemyStartUpData.h"
#include "AbilitySystem/SoulAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/SoulEnemyGameplayAbility.h"

void UDataAsset_EnemyStartUpData::GiveToAbilitySystemComponent(USoulAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
  Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

  if (!EnemyCombatAbilities.IsEmpty())
  {
    for (const TSubclassOf < USoulEnemyGameplayAbility >& AbilityClass : EnemyCombatAbilities)
    {
      if (!AbilityClass) continue;

      FGameplayAbilitySpec AbilitySpec(AbilityClass);
      AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
      AbilitySpec.Level = ApplyLevel;

      InASCToGive->GiveAbility(AbilitySpec);
    }
  }
}
