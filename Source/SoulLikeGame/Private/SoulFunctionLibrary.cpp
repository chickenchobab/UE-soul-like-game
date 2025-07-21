// Fill out your copyright notice in the Description page of Project Settings.


#include "SoulFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/SoulAbilitySystemComponent.h"

USoulAbilitySystemComponent* USoulFunctionLibrary::NativeGetSoulASCFromActor(AActor* InActor)
{
  check(InActor);

  return CastChecked<USoulAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void USoulFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	USoulAbilitySystemComponent* ASC = NativeGetSoulASCFromActor(InActor);

  if (!ASC->HasMatchingGameplayTag(TagToAdd))
  {
    ASC->AddLooseGameplayTag(TagToAdd);
  }
}

void USoulFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	USoulAbilitySystemComponent* ASC = NativeGetSoulASCFromActor(InActor);

  if (!ASC->HasMatchingGameplayTag(TagToRemove))
  {
    ASC->RemoveLooseGameplayTag(TagToRemove);
  }
}

bool USoulFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
  USoulAbilitySystemComponent* ASC = NativeGetSoulASCFromActor(InActor);

  return ASC->HasMatchingGameplayTag(TagToCheck);
}


void USoulFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, ESoulConfirmType& OutConfirmType)
{
  OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck) ? ESoulConfirmType::Yes : ESoulConfirmType::No;
}