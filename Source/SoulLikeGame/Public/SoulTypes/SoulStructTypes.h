// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SoulStructTypes.generated.h"

class USoulHeroLinkedAnimLayer;

USTRUCT(BlueprintType)
struct FSoulHeroWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<USoulHeroLinkedAnimLayer> WeaponAnimLayerToLink;
};