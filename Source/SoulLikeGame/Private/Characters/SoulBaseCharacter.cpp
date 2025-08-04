// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SoulBaseCharacter.h"
#include "AbilitySystem/SoulAbilitySystemComponent.h"
#include "AbilitySystem/SoulAttributeSet.h"
#include "MotionWarpingComponent.h"

// Sets default values
ASoulBaseCharacter::ASoulBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;

	SoulAbilitySystemComponent = CreateDefaultSubobject<USoulAbilitySystemComponent>(TEXT("SoulAbilitySystemComponent"));

	SoulAttributeSet = CreateDefaultSubobject<USoulAttributeSet>(TEXT("SoulAttributeSet"));

	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
}
 

UAbilitySystemComponent* ASoulBaseCharacter::GetAbilitySystemComponent() const
{
	return GetSoulAbilitySystemComponent();
}


UPawnCombatComponent* ASoulBaseCharacter::GetPawnCombatComponent() const 
{
	return nullptr;
}


UPawnUIComponent* ASoulBaseCharacter::GetPawnUIComponent() const 
{
	return nullptr;
}

void ASoulBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (SoulAbilitySystemComponent)
	{
		SoulAbilitySystemComponent->InitAbilityActorInfo(this, this);

		ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("Forgot to assign start up data to %s"), *GetName());
	}
}
