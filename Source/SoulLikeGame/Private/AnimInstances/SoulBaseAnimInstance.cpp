// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/SoulBaseAnimInstance.h"
#include "SoulFunctionLibrary.h"

bool USoulBaseAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
  if (APawn* OwningPawn = TryGetPawnOwner())
  {
    return USoulFunctionLibrary::NativeDoesActorHaveTag(OwningPawn, TagToCheck);
  }
  return false;
}