// Fill out your copyright notice in the Description page of Project Settings.


#include "SoulTypes/SoulStructTypes.h"
#include "AbilitySystem/Abilities/SoulGameplayAbility.h"

bool FSoulHeroAbilitySet::IsValid() const
{
  return InputTag.IsValid() && AbilityToGrant;
}