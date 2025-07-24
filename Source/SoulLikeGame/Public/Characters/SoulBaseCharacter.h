// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/PawnCombatInterface.h"
#include "SoulBaseCharacter.generated.h"

class USoulAbilitySystemComponent;
class USoulAttributeSet;
class UDataAsset_StartUpDataBase;

UCLASS()
class SOULLIKEGAME_API ASoulBaseCharacter : public ACharacter, public IAbilitySystemInterface, public IPawnCombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASoulBaseCharacter();
	
	FORCEINLINE USoulAbilitySystemComponent* GetSoulAbilitySystemComponent() const {return SoulAbilitySystemComponent;}
	
	FORCEINLINE USoulAttributeSet* GetSoulAttributeSet() const {return SoulAttributeSet;}

	//~ Begin IAbilitySystemInterface Interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface Interface

	//~ Begin IPawnCombatInterface Interface
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	//~ End IPawnCombatInterface Interface

protected:
	//~ Begin APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	USoulAbilitySystemComponent* SoulAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	USoulAttributeSet* SoulAttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<UDataAsset_StartUpDataBase> CharacterStartUpData;
};
