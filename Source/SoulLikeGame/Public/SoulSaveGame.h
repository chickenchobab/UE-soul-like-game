// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SoulTypes/SoulEnumTypes.h"
#include "SoulSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class SOULLIKEGAME_API USoulSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	ESoulGameDifficulty SavedCurrentGameDifficulty;
};
