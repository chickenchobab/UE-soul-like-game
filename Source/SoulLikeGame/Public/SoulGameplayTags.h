// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace SoulGameplayTags
{
	/** Input tags */
	SOULLIKEGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move)
	SOULLIKEGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look)
	SOULLIKEGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_EquipAxe)
	SOULLIKEGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UnequipAxe)

	/** Player tags */
	SOULLIKEGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Axe)
	SOULLIKEGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Unequip_Axe)

	SOULLIKEGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Axe)

	SOULLIKEGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Axe)
	SOULLIKEGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Axe)
}
