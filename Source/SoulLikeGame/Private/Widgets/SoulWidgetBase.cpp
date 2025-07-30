// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SoulWidgetBase.h"
#include "Interfaces/PawnUIInterface.h"
#include "Components/UI/HeroUIComponent.h"
#include "Components/UI/EnemyUIComponent.h"

void USoulWidgetBase::NativeOnInitialized()
{
  Super::NativeOnInitialized();

  if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(GetOwningPlayerPawn()))
  {
    if (UHeroUIComponent* HeroUIComponent = Cast<UHeroUIComponent>(PawnUIInterface->GetPawnUIComponent()))
    {
      BP_OnOwningHeroUIComponentInitialized(HeroUIComponent);
    }
    else if (UEnemyUIComponent* EnemyUIComponent = Cast<UEnemyUIComponent>(PawnUIInterface->GetPawnUIComponent()))
    {
      BP_OnOwningEnemyUIComponentInitialized(EnemyUIComponent);
    }
  }
}