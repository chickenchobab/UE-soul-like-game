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
	SOULLIKEGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LightAttack_Axe)
	SOULLIKEGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_HeavyAttack_Axe)

	/** Player tags */
	SOULLIKEGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Axe)
	SOULLIKEGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Unequip_Axe)
	SOULLIKEGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Axe)
	SOULLIKEGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Axe)
	SOULLIKEGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_HitPause)

	SOULLIKEGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Axe)

	SOULLIKEGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Axe)
	SOULLIKEGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Axe)
	SOULLIKEGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_HitPause)

	SOULLIKEGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_JumpToFinisher)

	SOULLIKEGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Light)
	SOULLIKEGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Heavy)

	/** Enemy tags */
	SOULLIKEGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee)
	SOULLIKEGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Ranged)

	SOULLIKEGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Weapon)

	SOULLIKEGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_Strafing)

	/** Shared tags */
	SOULLIKEGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_HitReact)
	SOULLIKEGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_Death)

	SOULLIKEGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_MeleeHit)
	SOULLIKEGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_HitReact)

	SOULLIKEGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_SetByCaller_BaseDamage)
	
	SOULLIKEGAME_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_Dead)
}
