// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SoulPickUpBase.generated.h"

class USphereComponent;

UCLASS()
class SOULLIKEGAME_API ASoulPickUpBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ASoulPickUpBase();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Pick Up Interaction")
	USphereComponent* PickUpCollisionSphere;

	UFUNCTION()
	virtual void OnCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
