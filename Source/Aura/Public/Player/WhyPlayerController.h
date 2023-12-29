// 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WhyPlayerController.generated.h"

class USplineComponent;
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
	void AutoRun();
	
	void CursorChase();
	IInteractableInterface* LastInteraction;
	IInteractableInterface* CurInteraction;
	FHitResult CursorHit;

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UWhyInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UWhyAbilitySystemComponent> WhyAbilitySystemComponent;

	UWhyAbilitySystemComponent* GetASC();

	FVector CachedDestination {FVector::ZeroVector};
	float FollowTime { 0.f };
	float ShortPressThreshold { 0.5f };
	bool bAutoRunning { false };
	bool bTargeting { false };

	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius { 50.f };

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> SplineComponent;
};
