// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/SoulBaseCharacter.h"
#include "SoulEnemyCharacter.generated.h"

class UEnemyCombatComponent;
class UEnemyUIComponent;
class UWidgetComponent;

/**
 * 
 */
UCLASS()
class SOULLIKEGAME_API ASoulEnemyCharacter : public ASoulBaseCharacter
{
	GENERATED_BODY()
	
public:
	ASoulEnemyCharacter();

	//~ Begin IPawnCombatInterface Interface
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	//~ End IPawnCombatInterface Interface

	//~ Begin IPawnUIInterface Interface
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	//~ End IPawnUIInterface Interface

	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }

protected:
	virtual void BeginPlay() override;

	//~ Begin APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UEnemyCombatComponent* EnemyCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UEnemyUIComponent* EnemyUIComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* EnemyHealthWidgetComponent;

private:
	void InitEnemyStartUpData();
};
