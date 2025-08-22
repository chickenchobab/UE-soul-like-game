// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/HeroGameplayAbility_PickUpStones.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Characters/SoulHeroCharacter.h"
#include "Items/PickUps/SoulStoneBase.h"
#include "Components/UI/HeroUIComponent.h"

void UHeroGameplayAbility_PickUpStones::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
  GetHeroUIComponentFromActorInfo()->OnStoneInteracted.Broadcast(true);

	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UHeroGameplayAbility_PickUpStones::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
  GetHeroUIComponentFromActorInfo()->OnStoneInteracted.Broadcast(true);
  
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}


void UHeroGameplayAbility_PickUpStones::CollectStones()
{
  CollectedStones.Empty();

  ASoulHeroCharacter* HeroCharacter = GetHeroCharacterFromActorInfo();

  TArray<FHitResult> TraceHits;

  UKismetSystemLibrary::BoxTraceMultiForObjects(
    HeroCharacter,
    HeroCharacter->GetActorLocation(),
    HeroCharacter->GetActorLocation() + -HeroCharacter->GetActorUpVector() * BoxTraceDistance,
    TraceBoxSize / 2.f,
    (-HeroCharacter->GetActorUpVector()).ToOrientationRotator(),
    StoneTraceChannel,
    false,
    TArray<AActor*>(),
    bDrawDebugShape ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
    TraceHits,
    true
  );

  for (const FHitResult& TraceHit : TraceHits)
  {
    if (ASoulStoneBase* FoundStone = Cast<ASoulStoneBase>(TraceHit.GetActor()))
    {
      CollectedStones.AddUnique(FoundStone);
    }
  }

  if (CollectedStones.IsEmpty())
  {
    CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
  }
}


void UHeroGameplayAbility_PickUpStones::ConsumeStones()
{
  if (CollectedStones.IsEmpty())
  {
    CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
    return;
  }

  for (ASoulStoneBase* CollectedStone : CollectedStones)
  {
    if (CollectedStone)
    {
      CollectedStone->Consume(GetSoulAbilityComponentFromActorInfo(), GetAbilityLevel());
    }
  }
}