// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "AbilitySystem/SoulAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/SoulGameplayAbility.h"


void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(USoulAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
  check(InASCToGive);

  GrantAbilities(ActivateOnGivenAbilities, InASCToGive, ApplyLevel);
  GrantAbilities(ReactiveAbilities, InASCToGive, ApplyLevel);
}


void UDataAsset_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<USoulGameplayAbility>>& InAbilitiesToGive, USoulAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
  if (InAbilitiesToGive.IsEmpty()) return;

  for (const TSubclassOf<USoulGameplayAbility>& Ability : InAbilitiesToGive)
  {
    if (!Ability) continue;

    FGameplayAbilitySpec AbilitySpec(Ability);
    AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
    AbilitySpec.Level = ApplyLevel;

    InASCToGive->GiveAbility(AbilitySpec);
  }
}
