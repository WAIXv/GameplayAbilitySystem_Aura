// 


#include "UI/HUD/WhyHUD.h"
#include "UI/WIdget/WhyUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

void AWhyHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class unitialized, please fill out BP_WhyHUD"))
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class unitialized, please fill out BP_WhyHUD"))
	
	OverlayWidget = CreateWidget<UWhyUserWidget>(GetWorld(), OverlayWidgetClass);

	const auto WidgetController = GetOverlayWidgetController({PC, PS, ASC, AS});
	OverlayWidget->SetWidgetController(WidgetController);

	OverlayWidget->AddToViewport();
}

UOverlayWidgetController* AWhyHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	static auto OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);

	static bool FirstInit {true};
	if (FirstInit)
	{
		OverlayWidgetController->SetWidgetControllerParam(WCParams);
		FirstInit = false;
	}

	return OverlayWidgetController;
}
