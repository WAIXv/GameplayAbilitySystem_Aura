// 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "WhyHUD.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UWhyWidgetController;
struct FWidgetControllerParams;
class UOverlayWidgetController;
class UWhyUserWidget;

/**
 * 
 */
UCLASS()
class AURA_API AWhyHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UWhyUserWidget> OverlayWidget;

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

	UFUNCTION(BlueprintCallable)
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UWhyUserWidget> OverlayWidgetClass;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
};
