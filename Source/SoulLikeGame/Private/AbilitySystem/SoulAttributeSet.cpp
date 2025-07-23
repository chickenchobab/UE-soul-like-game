// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/SoulAttributeSet.h"

USoulAttributeSet::USoulAttributeSet()
{
  InitCurrentHealth(1.f);
  InitMaxHealth(1.f);
  InitCurrentRange(1.f);
  InitMaxRange(1.f);
  InitAttackPower(1.f);
  InitDefensePower(1.f);
}
