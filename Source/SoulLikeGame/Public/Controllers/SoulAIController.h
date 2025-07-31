// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SoulAIController.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;

/**
 * 
 */
UCLASS()
class SOULLIKEGAME_API ASoulAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ASoulAIController(const FObjectInitializer& ObjectInitializer);
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAIPerceptionComponent* EnemyPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAISenseConfig_Sight* AISenseConfig_Sight;

	UFUNCTION()
	virtual void OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
};
