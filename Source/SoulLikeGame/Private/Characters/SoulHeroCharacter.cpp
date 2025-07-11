// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SoulHeroCharacter.h"
#include "SoulDebugHelper.h"

void ASoulHeroCharacter::BeginPlay()
{
	Super::BeginPlay();

  Debug::Print(TEXT("Working"));
}