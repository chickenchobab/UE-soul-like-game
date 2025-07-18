// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/SoulBaseAnimInstance.h"
#include "SoulHeroLinkedAnimLayer.generated.h"

class USoulHeroAnimInstance;

/**
 * 
 */
UCLASS()
class SOULLIKEGAME_API USoulHeroLinkedAnimLayer : public USoulBaseAnimInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	USoulHeroAnimInstance* GetHeroAnimInstance() const;
};
