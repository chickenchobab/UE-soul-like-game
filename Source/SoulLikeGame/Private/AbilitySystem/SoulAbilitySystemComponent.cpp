// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/SoulAbilitySystemComponent.h"

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