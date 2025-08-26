// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SoulTypes/SoulEnumTypes.h"
#include "SoulFunctionLibrary.generated.h"

class USoulAbilitySystemComponent;
class UPawnCombatComponent;
struct FScalableFloat;
class USoulGameInstance;

/**
 * 
 */
UCLASS()
class SOULLIKEGAME_API USoulFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static USoulAbilitySystemComponent* NativeGetSoulASCFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary")
	static void RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);

	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary", meta = (DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs = "OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, ESoulConfirmType& OutConfirmType);

	static UPawnCombatComponent* NativeGetCombatComponentFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary", meta = (DisplayName = "Get Pawn Combat Component From Actor", ExpandEnumAsExecs = "OutValidType"))
	static UPawnCombatComponent* BP_GetCombatComponentFromActor(AActor* InActor, ESoulValidType& OutValidType);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary")
	static bool IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn);

	UFUNCTION(BlueprintPure, Category = "FunctionLibrary", meta = (CompactNodeTitle = "Get Value At Level"))
	static float GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel = 1.f);

	UFUNCTION(BlueprintPure, Category = "FunctionLibrary")
	static FGameplayTag ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference);

	UFUNCTION(BlueprintPure, Category = "FunctionLibrary")
	static bool IsValidBlock(AActor* InAttacker, AActor* InDefender);

	UFUNCTION(BlueprintPure, Category = "FunctionLibrary")
	static bool ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor, const FGameplayEffectSpecHandle& InSpecHandle);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary", meta = (Latent, WorldContext = "WorldContextObject", LatentInfo = "LatentInfo", ExpandEnumAsExecs = "CountDownInput|CountDownOutput", TotalTime = "1.0", UpdateInterval = "0.1"))
	static void CountDown(const UObject* WorldContextObject, 
		float TotalTime, float UpdateInterval, float& OutRemainingTime, 
		ESoulCountDownActionInput CountDownInput, UPARAM(DisplayName = "Output") ESoulCountDownActionOutput& CountDownOutput,
		FLatentActionInfo LatentInfo
	);

	UFUNCTION(BlueprintPure, Category = "FunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static USoulGameInstance* GetSoulGameInstance(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static void ToggleInputMode(const UObject* WorldContextObject, ESoulInputMode InInputMode);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary")
	static void SaveCurrentGameDifficulty(ESoulGameDifficulty InDifficultyToSave);

	UFUNCTION(BlueprintCallable, Category = "FunctionLibrary")
	static bool TryLoadSavedGameDifficulty(ESoulGameDifficulty& OutSavedDifficulty);
};