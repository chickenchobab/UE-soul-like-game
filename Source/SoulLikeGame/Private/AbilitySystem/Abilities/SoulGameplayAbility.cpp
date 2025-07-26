// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/SoulGameplayAbility.h"
#include "AbilitySystem/SoulAbilitySystemComponent.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

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
  // What if the avatar have multiple UPawnCombatComponent
  return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}


USoulAbilitySystemComponent* USoulGameplayAbility::GetSoulAbilityComponentFromActorInfo() const
{
  return Cast<USoulAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}


FActiveGameplayEffectHandle USoulGameplayAbility::NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle)
{
  UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

  check(TargetASC && InSpecHandle.IsValid());

  return GetSoulAbilityComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(
    *InSpecHandle.Data,
    TargetASC
  );
}


FActiveGameplayEffectHandle USoulGameplayAbility::BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, ESoulSuccessType& OutSuccessType)
{
  FActiveGameplayEffectHandle ActiveGameplayEffectHandle = NativeApplyEffectSpecHandleToTarget(TargetActor, InSpecHandle);

  OutSuccessType = ActiveGameplayEffectHandle.WasSuccessfullyApplied() ? ESoulSuccessType::Successful : ESoulSuccessType::Failed;

  return ActiveGameplayEffectHandle;
}

