// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/SoulAIController.h"
#include "Navigation/CrowdFollowingComponent.h"

#include "SoulDebugHelper.h"

ASoulAIController::ASoulAIController(const FObjectInitializer& ObjectInitializer)
  : Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{
  if (UCrowdFollowingComponent* CrowdFollowingComp = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
  {
    Debug::Print(TEXT("CrowdFollowingComponent valid"), FColor::Green);
  }
}