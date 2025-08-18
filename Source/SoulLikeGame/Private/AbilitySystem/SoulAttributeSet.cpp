// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/SoulAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "SoulFunctionLibrary.h"
#include "SoulGameplayTags.h"
#include "Interfaces/PawnUIInterface.h"
#include "Components/UI/PawnUIComponent.h"
#include "Components/UI/HeroUIComponent.h"

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
  if (!CachedPawnUIInterface.IsValid())
  {
    CachedPawnUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor());
  }

  checkf(CachedPawnUIInterface.IsValid(), TEXT("%s did not implement IPawnUIInterface."), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());

  UPawnUIComponent* PawnUICoponent = CachedPawnUIInterface->GetPawnUIComponent();

  checkf(PawnUICoponent, TEXT("Could not extract a UPawnUIComponent from %s"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());


  if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
  {
    const float NewHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());

    SetCurrentHealth(NewHealth);

    PawnUICoponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
  }

  if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
  {
    const float NewRage = FMath::Clamp(GetCurrentRage(), 0.f, GetMaxRage());

    SetCurrentRage(NewRage);

    if (GetCurrentRage() == GetMaxRage())
    {
      USoulFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), SoulGameplayTags::Player_Status_Rage_Full);
    }
    else if (GetCurrentRage() == 0.f)
    {
      USoulFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), SoulGameplayTags::Player_Status_Rage_None);
    }
    else
    {
      USoulFunctionLibrary::RemoveGameplayTagFromActorIfFound(Data.Target.GetAvatarActor(), SoulGameplayTags::Player_Status_Rage_Full);
      USoulFunctionLibrary::RemoveGameplayTagFromActorIfFound(Data.Target.GetAvatarActor(), SoulGameplayTags::Player_Status_Rage_None);
    }

    if (UHeroUIComponent* HeroUIComponent = Cast<UHeroUIComponent>(PawnUICoponent))
    {
      HeroUIComponent->OnCurrentRageChanged.Broadcast(GetCurrentRage() / GetMaxRage());
    }
  }

  if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
  {
    const float OldHealth = GetCurrentHealth();
    const float DamageDone = GetDamageTaken();

    const float NewHealth = FMath::Clamp(OldHealth - DamageDone, 0.f, GetMaxHealth());

    SetCurrentHealth(NewHealth);

    PawnUICoponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());

    if (GetCurrentHealth() == 0.f)
    {
      USoulFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), SoulGameplayTags::Shared_Status_Dead);
    }
  }
}
