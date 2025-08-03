// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/SoulEnemyGameplayAbility.h"
#include "Characters/SoulEnemyCharacter.h"
#include "AbilitySystem/SoulAbilitySystemComponent.h"
#include "SoulGameplayTags.h"

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

FGameplayEffectSpecHandle USoulEnemyGameplayAbility::MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat)
{
  check(EffectClass);

  FGameplayEffectContextHandle ContextHandle = GetSoulAbilityComponentFromActorInfo()->MakeEffectContext();
  ContextHandle.SetAbility(this);
  ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
  ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

  FGameplayEffectSpecHandle EffectSpecHandle = GetSoulAbilityComponentFromActorInfo()->MakeOutgoingSpec(
    EffectClass,
    GetAbilityLevel(),
    ContextHandle
  );

  EffectSpecHandle.Data->SetSetByCallerMagnitude(
    SoulGameplayTags::Shared_SetByCaller_BaseDamage,
    InDamageScalableFloat.GetValueAtLevel(GetAbilityLevel())
  );

  return EffectSpecHandle;
}