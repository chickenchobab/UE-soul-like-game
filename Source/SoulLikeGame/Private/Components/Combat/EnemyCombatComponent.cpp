// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/EnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "SoulGameplayTags.h"

#include "SoulDebugHelper.h"

void UEnemyCombatComponent::OnWeaponHitTargetActor(AActor* HitActor)
{
  if (OverlappedActors.Contains(HitActor)) return;

  OverlappedActors.AddUnique(HitActor);

  bool bIsValidBlock = false;

  const bool bIsPlayerBlocking = false;
  const bool bIsMyAttackUnblockable = false;

  if (bIsPlayerBlocking && !bIsMyAttackUnblockable)
  {
    //TODO::Check if the block is valid
  }

  FGameplayEventData EventData;
  EventData.Instigator = GetOwningPawn();
  EventData.Target = HitActor;

  if (bIsValidBlock)
  {
    //TODO::Handle successful block
  }
  else
  {
    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
      GetOwningPawn(),
      SoulGameplayTags::Shared_Event_MeleeHit,
      EventData
    );
  }
}
