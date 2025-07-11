// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SoulBaseCharacter.h"
#include "SoulHeroCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SOULLIKEGAME_API ASoulHeroCharacter : public ASoulBaseCharacter
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
};

