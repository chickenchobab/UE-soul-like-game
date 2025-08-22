// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PickUps/SoulStoneBase.h"
#include "Characters/SoulHeroCharacter.h"
#include "AbilitySystem/SoulAbilitySystemComponent.h"
#include "SoulGameplayTags.h"


void ASoulStoneBase::Consume(USoulAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel)
{
  check(StoneGameplayEffectClass);

  UGameplayEffect* EffectCDO = StoneGameplayEffectClass->GetDefaultObject<UGameplayEffect>();

  AbilitySystemComponent->ApplyGameplayEffectToSelf(
    EffectCDO,
    ApplyLevel,
    AbilitySystemComponent->MakeEffectContext()
  );

  BP_OnStoneConsumed();
}


void ASoulStoneBase::OnCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
  if (ASoulHeroCharacter* OverlappedHeroCharacter = Cast<ASoulHeroCharacter>(OtherActor))
  {
    OverlappedHeroCharacter->GetSoulAbilitySystemComponent()->TryActivateAbilityByTag(SoulGameplayTags::Player_Ability_PickUp_Stones);
  }
}
