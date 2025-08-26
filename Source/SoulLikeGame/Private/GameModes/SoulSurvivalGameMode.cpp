// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/SoulSurvivalGameMode.h"
#include "Engine/AssetManager.h"
#include "Characters/SoulEnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"
#include "NavigationSystem.h"
#include "SoulFunctionLibrary.h"

#include "SoulDebugHelper.h"


void ASoulSurvivalGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
  Super::InitGame(MapName, Options, ErrorMessage);

  ESoulGameDifficulty SavedGameDifficulty;

  if (USoulFunctionLibrary::TryLoadSavedGameDifficulty(SavedGameDifficulty))
  {
    CurrentGameDifficulty = SavedGameDifficulty;
  }
}


void ASoulSurvivalGameMode::BeginPlay()
{
	Super::BeginPlay();

  checkf(EnemyWaveSpawnerDataTable, TEXT("Forgot to assign a valid data table in survival game mode bluprint"));

  SetCurrentSurvivalGameModeState(ESoulSurvivalGameModeState::WaitSpawnNewWave);

  TotalWavesToSpawn = EnemyWaveSpawnerDataTable->GetRowNames().Num();

  PreLoadNextWaveEnemies();
}

void ASoulSurvivalGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

  if (CurrentSurvivalGameModeState == ESoulSurvivalGameModeState::WaitSpawnNewWave)
  {
    ElapsedTime += DeltaTime;

    if (ElapsedTime >= SpawnNewWaveWaitTime)
    {
      ElapsedTime = 0.f;

      SetCurrentSurvivalGameModeState(ESoulSurvivalGameModeState::SpawningNewWave); 
    }
  }

  if (CurrentSurvivalGameModeState == ESoulSurvivalGameModeState::SpawningNewWave)
  {
    ElapsedTime += DeltaTime;

    if (ElapsedTime >= SpawnEnemiesDelayTime)
    {
      CurrentSpawnedEnemiesCounter += TrySpawnEnemies();

      ElapsedTime = 0.f;

      SetCurrentSurvivalGameModeState(ESoulSurvivalGameModeState::InProgress); 
    }
  }

  if (CurrentSurvivalGameModeState == ESoulSurvivalGameModeState::WaveCompleted)
  {
    ElapsedTime += DeltaTime;

    if (ElapsedTime >= WaveCompletedWaitTime)
    {
      ElapsedTime = 0.f;

      ++CurrentWaveCount;

      if (HasFinishedAllWaves())
      {
        SetCurrentSurvivalGameModeState(ESoulSurvivalGameModeState::AllWavesDone); 
      }
      else
      {
        SetCurrentSurvivalGameModeState(ESoulSurvivalGameModeState::WaitSpawnNewWave); 
        PreLoadNextWaveEnemies();
      }
    }
  }
}


void ASoulSurvivalGameMode::SetCurrentSurvivalGameModeState(ESoulSurvivalGameModeState InState)
{
  CurrentSurvivalGameModeState = InState;

  OnSurvivalGameModeStateChanged.Broadcast(CurrentSurvivalGameModeState);
}


bool ASoulSurvivalGameMode::HasFinishedAllWaves() const
{
  return CurrentWaveCount > TotalWavesToSpawn;
}


void ASoulSurvivalGameMode::PreLoadNextWaveEnemies()
{
  if (HasFinishedAllWaves()) return;

  PreLoadedEnemyClassMap.Empty();

  for (const FSoulEnemySpawnInfo& SpawnerInfo : GetCurrentWaveSpawnerTableRow()->EnemySpawnDefinitions)
  {
    if (SpawnerInfo.SoftEnemyClassToSpawn.IsNull()) continue;

    UAssetManager::GetStreamableManager().RequestAsyncLoad(
      SpawnerInfo.SoftEnemyClassToSpawn.ToSoftObjectPath(),
      FStreamableDelegate::CreateLambda(
        [SpawnerInfo, this]()
        {
          if (UClass* LoadedEnemyClass = SpawnerInfo.SoftEnemyClassToSpawn.Get())
          {
            PreLoadedEnemyClassMap.Emplace(SpawnerInfo.SoftEnemyClassToSpawn, LoadedEnemyClass);
          }
        }
      )
    );
  }
}


FSoulEnemyWaveSpawnerTableRow* ASoulSurvivalGameMode::GetCurrentWaveSpawnerTableRow() const
{
  const FName RowName = FName(TEXT("Wave") + FString::FromInt(CurrentWaveCount));

  FSoulEnemyWaveSpawnerTableRow* FoundRow = EnemyWaveSpawnerDataTable->FindRow<FSoulEnemyWaveSpawnerTableRow>(RowName, FString());

  checkf(FoundRow, TEXT("Could not find a valid row under the the name %s in the data table"), *RowName.ToString());

  return FoundRow;
}


int32 ASoulSurvivalGameMode::TrySpawnEnemies()
{
  if (TargetPointArray.IsEmpty())
  {
    UGameplayStatics::GetAllActorsOfClass(this, ATargetPoint::StaticClass(), TargetPointArray);
  }

  checkf(!TargetPointArray.IsEmpty(), TEXT("No valid target point found in level : %s for spawning enemies"), *GetWorld()->GetName());

  uint32 EnemiesSpawnedThisTime = 0;

  FActorSpawnParameters SpawnParam;
  SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

  for (const FSoulEnemySpawnInfo& SpanwerInfo : GetCurrentWaveSpawnerTableRow()->EnemySpawnDefinitions)
  {
    if (SpanwerInfo.SoftEnemyClassToSpawn.IsNull()) continue;

    const int32 NumToSpawn = FMath::RandRange(SpanwerInfo.MinPerSpawnCount, SpanwerInfo.MaxPerSpawnCount);

    UClass* LoadedEnemyClass = PreLoadedEnemyClassMap.FindChecked(SpanwerInfo.SoftEnemyClassToSpawn);

    for (int32 i = 0; i < NumToSpawn; ++i)
    {
      const int32 RandomTargetPointIndex = FMath::RandRange(0, TargetPointArray.Num() - 1);
      const FVector SpawnOrigin = TargetPointArray[RandomTargetPointIndex]->GetActorLocation();
      const FRotator SpawnRotation = TargetPointArray[RandomTargetPointIndex]->GetActorForwardVector().ToOrientationRotator();

      FVector SpawnLocation;
      UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(this, SpawnOrigin, SpawnLocation, 400.f);

      SpawnLocation += FVector(0.f, 0.f, 150.f);

      ASoulEnemyCharacter* SpawnedEnemy = GetWorld()->SpawnActor<ASoulEnemyCharacter>(LoadedEnemyClass, SpawnLocation, SpawnRotation, SpawnParam);

      if (SpawnedEnemy)
      {
        SpawnedEnemy->OnDestroyed.AddUniqueDynamic(this, &ThisClass::OnEnemyDestroyed);

        ++EnemiesSpawnedThisTime;
        ++TotalSpawnedEnemiesThisWaveCounter;
      }

      if (!ShouldKeepSpawnEnemies())
      {
        return EnemiesSpawnedThisTime;
      }
    }
  }

  return EnemiesSpawnedThisTime;
}


bool ASoulSurvivalGameMode::ShouldKeepSpawnEnemies() const
{
  return TotalSpawnedEnemiesThisWaveCounter < GetCurrentWaveSpawnerTableRow()->TotalEnemyToSpawnThisWave;
}


void ASoulSurvivalGameMode::OnEnemyDestroyed(AActor* DestroyedActor)
{
  --CurrentSpawnedEnemiesCounter;

  if (ShouldKeepSpawnEnemies())
  {
    CurrentSpawnedEnemiesCounter += TrySpawnEnemies();
  }
  else if (CurrentSpawnedEnemiesCounter == 0)
  {
    TotalSpawnedEnemiesThisWaveCounter = 0;
    CurrentSpawnedEnemiesCounter = 0;

    SetCurrentSurvivalGameModeState(ESoulSurvivalGameModeState::WaveCompleted);
  }
}


void ASoulSurvivalGameMode::RegisterSpawnedEnemies(const TArray<ASoulEnemyCharacter*>& InEnemiesToRegister)
{
  for (ASoulEnemyCharacter* SpawnedEnemy : InEnemiesToRegister)
  {
    if (SpawnedEnemy)
    {
      ++CurrentSpawnedEnemiesCounter;
      SpawnedEnemy->OnDestroyed.AddDynamic(this, &ThisClass::OnEnemyDestroyed);
    }
  }
}