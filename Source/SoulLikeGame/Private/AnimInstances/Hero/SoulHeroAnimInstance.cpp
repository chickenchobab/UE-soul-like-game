// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Hero/SoulHeroAnimInstance.h"
#include "Characters/SoulHeroCharacter.h"

void USoulHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

  if (OwningCharacter)
  {
    OwningHeroCharacter = Cast<ASoulHeroCharacter>(OwningCharacter);
  }
}

void USoulHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

  if (bHasAcceleration)
  {
    IdleElapsedTime = 0.f;
    bShouldEnterRelaxState = false;
  }
  else
  {
    IdleElapsedTime += DeltaSeconds;
    bShouldEnterRelaxState = (IdleElapsedTime >= EnterRelaxStateThreshold);
  }
}