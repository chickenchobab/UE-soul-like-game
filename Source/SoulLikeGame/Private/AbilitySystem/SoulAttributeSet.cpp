// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/SoulAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "SoulFunctionLibrary.h"
#include "SoulGameplayTags.h"

#include "SoulDebugHelper.h"

USoulAttributeSet::USoulAttributeSet()
{
  InitCurrentHealth(1.f);
  InitMaxHealth(1.f);
  InitCurrentRage(1.f);
  InitMaxRage(1.f);
  InitAttackPower(1.f);
  InitDefensePower(1.f);
}


void USoulAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data)
{
  if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
  {
    const float NewHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());

    SetCurrentHealth(NewHealth);
  }

  if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
  {
    const float NewRage = FMath::Clamp(GetCurrentRage(), 0.f, GetMaxRage());

    SetCurrentRage(NewRage);
  }

  if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
  {
    const float OldHealth = GetCurrentHealth();
    const float DamageDone = GetDamageTaken();

    const float NewHealth = FMath::Clamp(OldHealth - DamageDone, 0.f, GetMaxHealth());

    SetCurrentHealth(NewHealth);

    const FString DebugString = FString::Printf(
      TEXT("Old Health : %f, Damage Done : %f, NewHealth : %f"),
      OldHealth, DamageDone, NewHealth
    );
    Debug::Print(DebugString, FColor::Green);

    // TODO : Notify the UI

    if (NewHealth == 0.f)
    {
      USoulFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), SoulGameplayTags::Shared_Status_Dead);
    }
  }
}
