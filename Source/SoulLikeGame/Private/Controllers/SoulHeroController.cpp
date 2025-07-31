// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/SoulHeroController.h"

ASoulHeroController::ASoulHeroController()
{
	HeroTeamId = FGenericTeamId(0);
}

FGenericTeamId ASoulHeroController::GetGenericTeamId() const
{
	return HeroTeamId;
}