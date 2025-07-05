// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ACPlayerCharacter::ACPlayerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;
	
	ViewCam = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCam"));
	ViewCam->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	bUseControllerRotationYaw = false;
}

void ACPlayerCharacter::PawnClientRestart()
{
	Super::PawnClientRestart();

	APlayerController* OwningPlayerController = GetController<APlayerController>();
	if (OwningPlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* InputSubsystem = OwningPlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		if (InputSubsystem)
		{
			InputSubsystem->RemoveMappingContext(GameplayInputMappingContext);
			InputSubsystem->AddMappingContext(GameplayInputMappingContext, 0);
		}
	}	
}

void ACPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComp)
	{
		EnhancedInputComp->BindAction(JumpInputAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::Jump);
        EnhancedInputComp->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &ACPlayerCharacter::HandleLoopInput);
	};
}

void ACPlayerCharacter::HandleLoopInput(const FInputActionValue& InputActionValue)
{
	 FVector2D InputVal = InputActionValue.Get<FVector2D>();
	 AddControllerYawInput(InputVal.X);
	 AddControllerPitchInput(-InputVal.Y);
}
