// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SoulHeroCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "Components/Input/SoulInputComponent.h"
#include "SoulGameplayTags.h"
#include "AbilitySystem/SoulAbilitySystemComponent.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "Components/Combat/HeroCombatComponent.h"
#include "Components/UI/HeroUIComponent.h"

#include "SoulDebugHelper.h"


ASoulHeroCharacter::ASoulHeroCharacter()
{
  GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
  
  bUseControllerRotationPitch = false;
  bUseControllerRotationRoll = false;
  bUseControllerRotationYaw = false;

  CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
  CameraBoom->SetupAttachment(RootComponent);
  CameraBoom->TargetArmLength = 200.f;
  CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
  CameraBoom->bUsePawnControlRotation = true;

  FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
  FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
  FollowCamera->bUsePawnControlRotation = false;

  GetCharacterMovement()->bOrientRotationToMovement = true;
  GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
  GetCharacterMovement()->MaxWalkSpeed = 400.f;
  GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

  HeroCombatComponent = CreateDefaultSubobject<UHeroCombatComponent>(TEXT("HeroCombatComponent"));

  HeroUIComponent = CreateDefaultSubobject<UHeroUIComponent>(TEXT("HeroUIComponent"));
}


UPawnCombatComponent* ASoulHeroCharacter::GetPawnCombatComponent() const 
{
  return HeroCombatComponent;
}


UPawnUIComponent* ASoulHeroCharacter::GetPawnUIComponent() const 
{
  return HeroUIComponent;
}


void ASoulHeroCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
  checkf(InputConfigDataAsset, TEXT("Forgot to assign a valid data asset as input config"));
  
  ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
  UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

  check(Subsystem);

  Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);
  USoulInputComponent* SoulInputComponent = CastChecked<USoulInputComponent>(PlayerInputComponent);
  
  SoulInputComponent->BindNativeInputAction(InputConfigDataAsset, SoulGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
  SoulInputComponent->BindNativeInputAction(InputConfigDataAsset, SoulGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);

  SoulInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &ThisClass::Input_AbilityInputPressed, &ThisClass::Input_AbilityInputReleased);
}


void ASoulHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
}


void ASoulHeroCharacter::PossessedBy(AController* NewController)
{
  Super::PossessedBy(NewController);

  if (!CharacterStartUpData.IsNull())
  {
    if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.LoadSynchronous())
    {
      LoadedData->GiveToAbilitySystemComponent(SoulAbilitySystemComponent);
    }
  }
}


void ASoulHeroCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
  const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
  const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

  const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
  AddMovementInput(ForwardDirection, MovementVector.Y);

  const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
  AddMovementInput(RightDirection, MovementVector.X);
}


void ASoulHeroCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
  const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

  AddControllerYawInput(LookAxisVector.X);
  AddControllerPitchInput(LookAxisVector.Y);
}

void ASoulHeroCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	SoulAbilitySystemComponent->OnAbilityInputPressed(InInputTag);
}

void ASoulHeroCharacter::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	SoulAbilitySystemComponent->OnAbilityInputReleased(InInputTag);
}