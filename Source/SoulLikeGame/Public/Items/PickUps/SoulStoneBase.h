// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/PickUps/SoulPickUpBase.h"
#include "SoulStoneBase.generated.h"

class USoulAbilitySystemComponent;
class UGameplayEffect;

/**
 * 
 */
UCLASS()
class SOULLIKEGAME_API ASoulStoneBase : public ASoulPickUpBase
{
	GENERATED_BODY()

public:
	void Consume(USoulAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel);

protected:
	virtual void OnCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Stone Consumed"))
	void BP_OnStoneConsumed();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> StoneGameplayEffectClass;
};
