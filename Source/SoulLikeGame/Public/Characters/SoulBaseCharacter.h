// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "SoulBaseCharacter.generated.h"

class USoulAbilitySystemComponent;
class USoulAttributeSet;

UCLASS()
class SOULLIKEGAME_API ASoulBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASoulBaseCharacter();
	
	FORCEINLINE USoulAbilitySystemComponent* GetSoulAbilitySystemComponent() const {return SoulAbilitySystemComponent;}
	
	FORCEINLINE USoulAttributeSet* GetSoulAttributeSet() const {return SoulAttributeSet;}

	//~ Begin UAbilitySystemInterface Interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;
	//~ End UAbilitySystemInterface Interface

protected:
	//~ Begin APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	USoulAbilitySystemComponent* SoulAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	USoulAttributeSet* SoulAttributeSet;
};
