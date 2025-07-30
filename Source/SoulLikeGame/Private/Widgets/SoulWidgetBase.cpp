// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/SoulWidgetBase.h"
#include "Interfaces/PawnUIInterface.h"
#include "Components/UI/HeroUIComponent.h"
#include "Components/UI/EnemyUIComponent.h"

#include "SoulDebugHelper.h"

void USoulWidgetBase::NativeOnInitialized()
{
  Super::NativeOnInitialized();

  if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(GetOwningPlayerPawn()))
  {
    if (UHeroUIComponent* HeroUIComponent = Cast<UHeroUIComponent>(PawnUIInterface->GetPawnUIComponent()))
    {
      BP_OnOwningHeroUIComponentInitialized(HeroUIComponent);
    }
  }
}

void USoulWidgetBase::InitializeEnemyCreatedWidget(AActor* OwningEnemyActor)
{
  if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(OwningEnemyActor))
  {
    if (UEnemyUIComponent* EnemyUIComponent = Cast<UEnemyUIComponent>(PawnUIInterface->GetPawnUIComponent()))
    {
      BP_OnOwningEnemyUIComponentInitialized(EnemyUIComponent);
    }
  }
}
