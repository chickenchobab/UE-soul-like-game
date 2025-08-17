// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/SoulAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/SoulGameplayAbility.h"
#include "SoulGameplayTags.h"


void USoulAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid()) return;

  for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
  {
    if (!AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InInputTag)) continue;

    if (InInputTag.MatchesTag(SoulGameplayTags::InputTag_Toggleable) && AbilitySpec.IsActive())
    {
      CancelAbilityHandle(AbilitySpec.Handle);
    }
    else
    {
      TryActivateAbility(AbilitySpec.Handle);
    }
  }
}

void USoulAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid() || !InInputTag.MatchesTag(SoulGameplayTags::InputTag_MustBeHeld)) return;

  for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
  {
    if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InInputTag) && AbilitySpec.IsActive())
    {
      CancelAbilityHandle(AbilitySpec.Handle);
    }
  }
}


void USoulAbilitySystemComponent::GrantHeroWeaponAbilities(const TArray<FSoulHeroAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles)
{
  if (InDefaultWeaponAbilities.IsEmpty()) return;

  for (const FSoulHeroAbilitySet& AbilitySet : InDefaultWeaponAbilities)
  {
    if (!AbilitySet.IsValid()) continue;

    FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
    AbilitySpec.SourceObject = GetAvatarActor();
    AbilitySpec.Level = ApplyLevel;
    AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.InputTag);

    OutGrantedAbilitySpecHandles.AddUnique(GiveAbility(AbilitySpec));
  }
}


void USoulAbilitySystemComponent::RemoveGrantedHeroWeaponAbilities(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove)
{
  if (InSpecHandlesToRemove.IsEmpty()) return;

  for (const FGameplayAbilitySpecHandle& SpecHandle : InSpecHandlesToRemove)
  {
    if (SpecHandle.IsValid())
    {
      ClearAbility(SpecHandle);
    }
  }

  InSpecHandlesToRemove.Empty();
}


bool USoulAbilitySystemComponent::TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate)
{
  check(AbilityTagToActivate.IsValid());

  TArray<FGameplayAbilitySpec*> FoundAbilitySpecs;
  GetActivatableGameplayAbilitySpecsByAllMatchingTags(AbilityTagToActivate.GetSingleTagContainer(), FoundAbilitySpecs);

  if (!FoundAbilitySpecs.IsEmpty())
  {
    const int32 RandomAbilityIndex = FMath::RandRange(0, FoundAbilitySpecs.Num() - 1);
    FGameplayAbilitySpec* SpecToActivate = FoundAbilitySpecs[RandomAbilityIndex];
  
    check(SpecToActivate);
  
    if (!SpecToActivate->IsActive())
    {
      return TryActivateAbility(SpecToActivate->Handle);
    }
  }

  return false;
}
