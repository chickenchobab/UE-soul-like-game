// Fill out your copyright notice in the Description page of Project Settings.


#include "SoulGameInstance.h"


TSoftObjectPtr<UWorld> USoulGameInstance::GetGameLevelByTag(FGameplayTag InTag)
{
  for (const FSoulGameLevelSet& GameLevelSet : GameLevelSets)
  {
    if (!GameLevelSet.IsValid()) continue;

    if (GameLevelSet.LevelTag == InTag)
    {
      return GameLevelSet.Level;
    }
  }

  return TSoftObjectPtr<UWorld>();
}