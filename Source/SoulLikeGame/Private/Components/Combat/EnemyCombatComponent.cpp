// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/EnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "SoulGameplayTags.h"
#include "SoulFunctionLibrary.h"
#include "Characters/SoulEnemyCharacter.h"
#include "Components/BoxComponent.h"

#include "SoulDebugHelper.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
  if (OverlappedActors.Contains(HitActor)) return;

  OverlappedActors.AddUnique(HitActor);

  bool bIsValidBlock = false;

  const bool bIsPlayerBlocking = USoulFunctionLibrary::NativeDoesActorHaveTag(HitActor, SoulGameplayTags::Player_Status_Blocking);
  const bool bIsMyAttackUnblockable = USoulFunctionLibrary::NativeDoesActorHaveTag(GetOwningPawn(), SoulGameplayTags::Enemy_Status_Unblockable);

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


void UEnemyCombatComponent::ToggleBodyCollisionBoxCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
  ASoulEnemyCharacter* OwningEnemyCharacter = GetOwningPawn<ASoulEnemyCharacter>();

  check(OwningEnemyCharacter);

  UBoxComponent* LeftHandCollisionBox = OwningEnemyCharacter->GetLeftHandCollisionBox();
  UBoxComponent* RightHandCollisionBox = OwningEnemyCharacter->GetRightHandCollisionBox();

  check(LeftHandCollisionBox && RightHandCollisionBox);

  switch (ToggleDamageType)
  {
  case EToggleDamageType::LeftHand:
    LeftHandCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
    break;
  case EToggleDamageType::RightHand:
    RightHandCollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
    break;
  default:
    break;
  }
  
  if (!bShouldEnable)
  {
    OverlappedActors.Empty();
  }
}

