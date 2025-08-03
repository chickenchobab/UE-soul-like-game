// Fill out your copyright notice in the Description page of Project Settings.


#include "SoulFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/SoulAbilitySystemComponent.h"
#include "Interfaces/PawnCombatInterface.h"
#include "GenericTeamAgentInterface.h"

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

  if (ASC->HasMatchingGameplayTag(TagToRemove))
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

UPawnCombatComponent* USoulFunctionLibrary::NativeGetCombatComponentFromActor(AActor* InActor)
{
	check(InActor);

	if (IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
	{
		return PawnCombatInterface->GetPawnCombatComponent();
	}
	return nullptr;
}


UPawnCombatComponent* USoulFunctionLibrary::BP_GetCombatComponentFromActor(AActor* InActor, ESoulValidType& OutValidType)
{
  UPawnCombatComponent* CombatComponent = NativeGetCombatComponentFromActor(InActor);
  
  OutValidType = CombatComponent ? ESoulValidType::Valid : ESoulValidType::InValid;
  
  return CombatComponent;
}


bool USoulFunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
  check(QueryPawn && TargetPawn);

  IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
  IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

  if (QueryTeamAgent && TargetTeamAgent)
  {
    return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
  }
  return false;
}
