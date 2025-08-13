// Fill out your copyright notice in the Description page of Project Settings.


#include "SoulFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/SoulAbilitySystemComponent.h"
#include "Interfaces/PawnCombatInterface.h"
#include "GenericTeamAgentInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "SoulGameplayTags.h"

#include "SoulDebugHelper.h"

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


float USoulFunctionLibrary::GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel)
{
  return InScalableFloat.GetValueAtLevel(InLevel);
}



FGameplayTag USoulFunctionLibrary::ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference)
{
  check(InAttacker && InVictim);

  const FVector VictimForward = InVictim->GetActorForwardVector();
  const FVector AttackDirection = (InVictim->GetActorLocation() - InAttacker->GetActorLocation()).GetSafeNormal();

  const float DotResult = FVector::DotProduct(VictimForward, AttackDirection);

  OutAngleDifference = UKismetMathLibrary::DegAcos(DotResult);

  const FVector CrossResult = FVector::CrossProduct(VictimForward, AttackDirection);

  if (CrossResult.Z < 0.f)
  {
    OutAngleDifference *= -1.f;
  }

  if (OutAngleDifference >= -45.f && OutAngleDifference < 45.f)
  {
    return SoulGameplayTags::Shared_Status_HitReact_Back;
  }
  else if (OutAngleDifference >= 45.f && OutAngleDifference < 135.f)
  {
    return SoulGameplayTags::Shared_Status_HitReact_Left;
  }
  else if (OutAngleDifference < -45.f && OutAngleDifference >= -135.f)
  {
    return SoulGameplayTags::Shared_Status_HitReact_Right;
  }
  return SoulGameplayTags::Shared_Status_HitReact_Front;
}


bool USoulFunctionLibrary::IsValidBlock(AActor* InAttacker, AActor* InDefender)
{
  check(InAttacker && InDefender);

  const float DotResult = FVector::DotProduct(InAttacker->GetActorForwardVector(), InDefender->GetActorForwardVector());

  // const FString DebugString = FString::Printf(TEXT("Dot Result: %f %s"), DotResult, DotResult < -0.1f ? TEXT("Valid block") : TEXT("Invalid block"));
  // Debug::Print(DebugString, DotResult < -0.1f ? FColor::Green : FColor::Red);

  return DotResult < -0.1f;
}


bool USoulFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor, const FGameplayEffectSpecHandle& InSpecHandle)
{
  USoulAbilitySystemComponent* SourceASC = NativeGetSoulASCFromActor(InInstigator);
  USoulAbilitySystemComponent* TargetASC = NativeGetSoulASCFromActor(InTargetActor);

  FActiveGameplayEffectHandle ActiveGameplayEffectHandle = SourceASC->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data, TargetASC);

  return ActiveGameplayEffectHandle.WasSuccessfullyApplied();
}
