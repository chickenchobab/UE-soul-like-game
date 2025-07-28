// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GEExecCalc/GEExecCalc_DamageTaken.h"
#include "AbilitySystem/SoulAttributeSet.h"
#include "SoulGameplayTags.h"

#include "SoulDebugHelper.h"

struct FSoulDamageCapture
{
  DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
  DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
  DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

  FSoulDamageCapture()
  {
    DEFINE_ATTRIBUTE_CAPTUREDEF(USoulAttributeSet, AttackPower, Source, false)
    DEFINE_ATTRIBUTE_CAPTUREDEF(USoulAttributeSet, DefensePower, Target, false)
    DEFINE_ATTRIBUTE_CAPTUREDEF(USoulAttributeSet, DamageTaken, Target, false)
  }
};

static const FSoulDamageCapture& GetSoulDamageCapture()
{
  static FSoulDamageCapture SoulDamageCapture;
  return SoulDamageCapture;
}

UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{
  RelevantAttributesToCapture.Add(GetSoulDamageCapture().AttackPowerDef);
  RelevantAttributesToCapture.Add(GetSoulDamageCapture().DefensePowerDef);
  RelevantAttributesToCapture.Add(GetSoulDamageCapture().DamageTakenDef);
}


void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const 
{
  const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

  // EffectSpec.GetContext().GetSourceObject();
  // EffectSpec.GetContext().GetAbility();
  // EffectSpec.GetContext().GetInstigator();
  // EffectSpec.GetContext().GetEffectCauser();

  FAggregatorEvaluateParameters EvaluateParameters;
  EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
  EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

  float SourceAttackPower = 0.f;
  ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetSoulDamageCapture().AttackPowerDef, EvaluateParameters, SourceAttackPower);

  float BaseDamage = 0.f;
  int32 UsedLightAttackComboCount = 0;
  int32 UsedHeavyAttackComboCount = 0;

  for (const TPair<FGameplayTag, float> & TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
  {
    if (TagMagnitude.Key.MatchesTagExact(SoulGameplayTags::Shared_SetByCaller_BaseDamage))
    {
      BaseDamage = TagMagnitude.Value;
    }

    if (TagMagnitude.Key.MatchesTagExact(SoulGameplayTags::Player_SetByCaller_AttackType_Light))
    {
      UsedLightAttackComboCount = TagMagnitude.Value;
    }

    if (TagMagnitude.Key.MatchesTagExact(SoulGameplayTags::Player_SetByCaller_AttackType_Heavy))
    {
      UsedHeavyAttackComboCount = TagMagnitude.Value;
    }
  }

  float TargetDefensePower = 0.f;
  ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetSoulDamageCapture().DefensePowerDef, EvaluateParameters, TargetDefensePower);

  if (UsedLightAttackComboCount != 0)
  {
    const float DamageIncreasePercentLight = (UsedLightAttackComboCount - 1) * 0.05 + 1.f;
    BaseDamage *= DamageIncreasePercentLight;
  }

  if (UsedHeavyAttackComboCount != 0)
  {
    const float DamageIncreasePercentHeavy = UsedHeavyAttackComboCount * 0.15f + 1.f;
    BaseDamage *= DamageIncreasePercentHeavy;
  }
  
  const float FinalDamage = BaseDamage * SourceAttackPower / TargetDefensePower;

  if (FinalDamage > 0.f)
  {
    OutExecutionOutput.AddOutputModifier(
      FGameplayModifierEvaluatedData(
        GetSoulDamageCapture().DamageTakenProperty,
        EGameplayModOp::Override,
        FinalDamage
      )
    );
  }
}
