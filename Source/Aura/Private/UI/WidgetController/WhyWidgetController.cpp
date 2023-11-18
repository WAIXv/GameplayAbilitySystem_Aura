// 


#include "UI/WidgetController/WhyWidgetController.h"

void UWhyWidgetController::SetWidgetControllerParam(const FWidgetControllerParams WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UWhyWidgetController::BroadcastInitValues()
{
	// override in sub class
}

void UWhyWidgetController::BindCallbackToDepencies()
{
	// override in sub class
}
