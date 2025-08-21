// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "SoulTypes/SoulEnumTypes.h"
#include "SoulGameplayAbility.generated.h"

class UPawnCombatComponent;
class USoulAbilitySystemComponent;

UENUM(BlueprintType)
enum class ESoulAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};


/**
 * 
 */
UCLASS()
class SOULLIKEGAME_API USoulGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	//~ Begin UGameplayAbility Interface
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//~ End UGameplayAbility Interface

	UPROPERTY(EditDefaultsOnly, Category = "SoulAbility")
	ESoulAbilityActivationPolicy AbilityActivationPolicy = ESoulAbilityActivationPolicy::OnTriggered;
	
	UFUNCTION(BlueprintPure, Category = "SoulAbility")
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category = "SoulAbility")
	USoulAbilitySystemComponent* GetSoulAbilityComponentFromActorInfo() const;

	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle);

	UFUNCTION(BlueprintCallable, Category = "SoulAbility", meta = (DisplayName = "Apply Gameplay Effect Spec Handle To Target Actor", ExpandEnumAsExecs = "OutSuccessType"))
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, ESoulSuccessType& OutSuccessType);
	
	UFUNCTION(BlueprintCallable, Category = "SoulAbility")
	void ApplyGameplayEffectSpecHandleToHitResults(const FGameplayEffectSpecHandle& InSpecHandle, const TArray<FHitResult>& InHitResults);
};