// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/SoulGameplayAbility.h"
#include "AbilitySystem/SoulAbilitySystemComponent.h"
#include "Components/Combat/PawnCombatComponent.h"

void USoulGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

  if (AbilityActivationPolicy == ESoulAbilityActivationPolicy::OnGiven)
  {
    if (ActorInfo && !Spec.IsActive())
    {
      ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
    }
  }
}

void USoulGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

  if (AbilityActivationPolicy == ESoulAbilityActivationPolicy::OnGiven)
  {
    if (ActorInfo)
    {
      ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
    }
  }
}


UPawnCombatComponent* USoulGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
  // What if the avatar have multiple UPawnCombatComponent?
  return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}
