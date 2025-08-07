// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/EnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "SoulGameplayTags.h"
#include "SoulFunctionLibrary.h"

#include "SoulDebugHelper.h"

void UEnemyCombatComponent::OnWeaponHitTargetActor(AActor* HitActor)
{
  if (OverlappedActors.Contains(HitActor)) return;

  OverlappedActors.AddUnique(HitActor);

  bool bIsValidBlock = false;

  const bool bIsPlayerBlocking = USoulFunctionLibrary::NativeDoesActorHaveTag(HitActor, SoulGameplayTags::Player_Status_Blocking);
  const bool bIsMyAttackUnblockable = false;

  if (bIsPlayerBlocking && !bIsMyAttackUnblockable)
  {
    bIsValidBlock = USoulFunctionLibrary::IsValidBlock(GetOwningPawn(), HitActor);
  }

  FGameplayEventData EventData;
  EventData.Instigator = GetOwningPawn();
  EventData.Target = HitActor;

  if (bIsValidBlock)
  {
    UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
      HitActor,
      SoulGameplayTags::Player_Event_SuccessfulBlock,
      EventData
    );
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
