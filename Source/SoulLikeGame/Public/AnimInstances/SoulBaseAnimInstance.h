// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameplayTagContainer.h"
#include "SoulBaseAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SOULLIKEGAME_API USoulBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable, meta = (BlueprintThreadSafe))
	bool DoesOwnerHaveTag(FGameplayTag TagToCheck) const;
};
