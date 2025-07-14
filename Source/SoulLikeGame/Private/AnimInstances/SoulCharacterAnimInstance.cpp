// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/SoulCharacterAnimInstance.h"
#include "Characters/SoulBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void USoulCharacterAnimInstance::NativeInitializeAnimation()
{
  OwningCharacter = Cast<ASoulBaseCharacter>(TryGetPawnOwner());
  if (OwningCharacter)
  {
    OwningMovementComponent = OwningCharacter->GetCharacterMovement();
  }
}


void USoulCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
  if (!OwningCharacter || !OwningMovementComponent) return;

  GroundSpeed = OwningCharacter->GetVelocity().Size2D();
  bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
}
