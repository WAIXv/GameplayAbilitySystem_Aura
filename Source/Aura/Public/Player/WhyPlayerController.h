﻿// 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WhyPlayerController.generated.h"

class IInteractableInterface;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class AURA_API AWhyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AWhyPlayerController();
	virtual void PlayerTick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	void Move(const FInputActionValue& InputActionValue);

	void CursorChase();
	IInteractableInterface* LastInteraction;
	IInteractableInterface* CurInteraction;
};
