// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SoulEnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "Engine/AssetManager.h"
#include "DataAssets/StartUpData/DataAsset_EnemyStartUpData.h"

#include "SoulDebugHelper.h"

ASoulEnemyCharacter::ASoulEnemyCharacter()
{
  AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

  bUseControllerRotationPitch = false;
  bUseControllerRotationRoll = false;
  bUseControllerRotationYaw = false;

  GetCharacterMovement()->bUseControllerDesiredRotation = false;
  GetCharacterMovement()->bOrientRotationToMovement = true;
  GetCharacterMovement()->RotationRate = FRotator(0.f, 100.f, 0.f);
  GetCharacterMovement()->MaxWalkSpeed = 300.f;
  GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;

  EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>(TEXT("EnemyCombatComponent"));
}


UPawnCombatComponent* ASoulEnemyCharacter::GetPawnCombatComponent() const 
{
  return EnemyCombatComponent;
}


void ASoulEnemyCharacter::PossessedBy(AController* NewController)
{
  Super::PossessedBy(NewController);

  InitEnemyStartUpData();
}


void ASoulEnemyCharacter::InitEnemyStartUpData()
{
  if (CharacterStartUpData.IsNull()) return;

  UAssetManager::GetStreamableManager().RequestAsyncLoad(
    CharacterStartUpData.ToSoftObjectPath(),
    FStreamableDelegate::CreateLambda(
      [this]()
      {
        if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.Get())
        {
          LoadedData->GiveToAbilitySystemComponent(SoulAbilitySystemComponent);

          Debug::Print(TEXT("Enemy start up data loaded"), FColor::Green);
        }
      }
    )
  );
}
