// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/SoulAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/SoulGameplayAbility.h"


void USoulAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid()) return;

  for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
  {
    if (!AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InInputTag)) continue;
    TryActivateAbility(AbilitySpec.Handle);
  }
}

void USoulAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid()) return;
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