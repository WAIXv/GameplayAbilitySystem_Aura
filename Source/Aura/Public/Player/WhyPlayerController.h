// 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WhyPlayerController.generated.h"

class UWhyAbilitySystemComponent;
struct FGameplayTag;
struct FInputActionValue;
class UWhyInputConfig;
class IInteractableInterface;
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

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UWhyInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UWhyAbilitySystemComponent> WhyAbilitySystemComponent;

	UWhyAbilitySystemComponent* GetASC();
};
