// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/SoulHeroGameplayAbility.h"
#include "Characters/SoulHeroCharacter.h"
#include "Controllers/SoulHeroController.h"
#include "AbilitySystem/SoulAbilitySystemComponent.h"
#include "SoulGameplayTags.h"

ASoulHeroCharacter* USoulHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
  if (!CachedHeroCharacter.IsValid())
  {
    CachedHeroCharacter = Cast<ASoulHeroCharacter>(CurrentActorInfo->AvatarActor);
  }
  return CachedHeroCharacter.IsValid() ? CachedHeroCharacter.Get() : nullptr;
}


ASoulHeroController* USoulHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
  if (!CachedHeroController.IsValid())
  {
    CachedHeroController = Cast<ASoulHeroController>(CurrentActorInfo->PlayerController);
  }
  return CachedHeroController.IsValid() ? CachedHeroController.Get() : nullptr;
}


UHeroCombatComponent* USoulHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
  return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}


FGameplayEffectSpecHandle USoulHeroGameplayAbility::MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount)
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
    InWeaponBaseDamage
  );

  if (InCurrentAttackTypeTag.IsValid())
  {
    EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag, InUsedComboCount);
  }

  return EffectSpecHandle;
}
