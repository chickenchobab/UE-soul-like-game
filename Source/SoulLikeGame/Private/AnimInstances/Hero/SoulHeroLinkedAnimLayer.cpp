// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Hero/SoulHeroLinkedAnimLayer.h"
#include "AnimInstances/Hero/SoulHeroAnimInstance.h"

USoulHeroAnimInstance* USoulHeroLinkedAnimLayer::GetHeroAnimInstance() const
{
  return Cast<USoulHeroAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
