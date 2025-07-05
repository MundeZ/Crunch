// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CCharacter.h"
#include "CPlayerCharacter.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class ACPlayerCharacter : public ACCharacter
{
	GENERATED_BODY()
public:
	ACPlayerCharacter();
	virtual void PawnClientRestart() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	UPROPERTY(VisibleDefaultsOnly, Category="View")
	class USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleDefaultsOnly, Category="View")
	class UCameraComponent* ViewCam;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* JumpInputAction;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* LookInputAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputMappingContext* GameplayInputMappingContext;

	void HandleLoopInput(const FInputActionValue& InputActionValue);
};
