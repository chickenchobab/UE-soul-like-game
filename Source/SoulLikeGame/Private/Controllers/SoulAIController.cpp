// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/SoulAIController.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "SoulDebugHelper.h"

ASoulAIController::ASoulAIController(const FObjectInitializer& ObjectInitializer)
  : Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{
  AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("EnemySeneConfig_Sight");
  AISenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
  AISenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;
  AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;
  AISenseConfig_Sight->SightRadius = 5000.f;
  AISenseConfig_Sight->LoseSightRadius = 0.f;
  AISenseConfig_Sight->PeripheralVisionAngleDegrees = 360.f;

  EnemyPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("EnemyPerceptionComponent");
  EnemyPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);
  EnemyPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
  EnemyPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ThisClass::OnEnemyPerceptionUpdated);

  SetGenericTeamId(FGenericTeamId(1));
}

ETeamAttitude::Type ASoulAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
  const APawn* PawnToCheck = Cast<const APawn>(&Other);

  const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(PawnToCheck->GetController());

  if (OtherTeamAgent && OtherTeamAgent->GetGenericTeamId() != GetGenericTeamId())
  {
    return ETeamAttitude::Hostile;
  }
  return ETeamAttitude::Friendly;
}

void ASoulAIController::OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
  if (Stimulus.WasSuccessfullySensed() && Actor)
  {
    Debug::Print(Actor->GetActorNameOrLabel() + TEXT(" was sensed"), FColor::Green);
  }
}
