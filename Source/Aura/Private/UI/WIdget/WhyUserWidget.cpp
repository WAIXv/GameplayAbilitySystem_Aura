// 


#include "UI/WIdget/WhyUserWidget.h"

void UWhyUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
