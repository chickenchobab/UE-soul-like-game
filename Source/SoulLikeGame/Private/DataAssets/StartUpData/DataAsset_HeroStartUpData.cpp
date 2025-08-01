// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/DataAsset_HeroStartUpData.h"
#include "AbilitySystem/Abilities/SoulGameplayAbility.h"
#include "AbilitySystem/SoulAbilitySystemComponent.h"


void UDataAsset_HeroStartUpData::GiveToAbilitySystemComponent(USoulAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
  Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

  for (const FSoulHeroAbilitySet& AbilitySet: HeroStartUpAbilitlySets)
  {
    if (!AbilitySet.IsValid()) continue;

    FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
    AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
    AbilitySpec.Level = ApplyLevel;
    AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.InputTag);
    
    InASCToGive->GiveAbility(AbilitySpec);
  }
}

