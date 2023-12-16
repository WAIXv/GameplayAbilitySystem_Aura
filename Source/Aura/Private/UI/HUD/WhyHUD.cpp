// 


#include "UI/HUD/WhyHUD.h"
#include "UI/WIdget/WhyUserWidget.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"

void AWhyHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class unitialized, please fill out BP_WhyHUD"))
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class unitialized, please fill out BP_WhyHUD"))
	
	OverlayWidget = CreateWidget<UWhyUserWidget>(GetWorld(), OverlayWidgetClass);

	const auto WidgetController = GetOverlayWidgetController({PC, PS, ASC, AS});
	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadcastInitValues();
	
	OverlayWidget->AddToViewport();
}

UOverlayWidgetController* AWhyHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	// 耻辱柱
	// Static and NewObject??
	// GC??
	
	// static auto OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
	// OverlayWidgetController->AddToRoot();
	//
	// static bool FirstInit {true};
	// if (FirstInit)
	// {
	// 	OverlayWidgetController->SetWidgetControllerParam(WCParams);
	// 	OverlayWidgetController->BindCallbackToDepencies();
	// 	FirstInit = false;
	// }
	
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
	
		OverlayWidgetController->SetWidgetControllerParam(WCParams);
		OverlayWidgetController->BindCallbackToDepencies();
	}

	return OverlayWidgetController;
}

UAttributeMenuWidgetController* AWhyHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams WCParams)
{
	if (AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
	
		AttributeMenuWidgetController->SetWidgetControllerParam(WCParams);
		AttributeMenuWidgetController->BindCallbackToDepencies();
	}

	return AttributeMenuWidgetController;
}
