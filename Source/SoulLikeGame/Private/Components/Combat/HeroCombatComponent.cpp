// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/HeroCombatComponent.h"
#include "Items/Weapons/SoulHeroWeapon.h"

#include "SoulDebugHelper.h"

ASoulHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag)
{
  return Cast<ASoulHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

void UHeroCombatComponent::OnWeaponHitTargetActor(AActor* HitActor)
{
	if (OverlappedActors.Contains(HitActor)) return;

  OverlappedActors.AddUnique(HitActor);
}

void UHeroCombatComponent::OnWeaponDetachFromTargetActor(AActor* HitActor)
{
	Debug::Print(GetOwningPawn()->GetActorNameOrLabel() + TEXT(" 's weapon pulled from ") + HitActor->GetActorNameOrLabel(), FColor::Red);
}