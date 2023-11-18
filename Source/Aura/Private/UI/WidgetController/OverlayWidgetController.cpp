// 


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/WhyAttributeSet.h"

void UOverlayWidgetController::BroadcastInitValues()
{
	const auto WhyAttributeSet = CastChecked<UWhyAttributeSet>(AttributeSet);
	
	OnHealthChanged.Broadcast(WhyAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(WhyAttributeSet->GetMaxHealth());
}

void UOverlayWidgetController::BindCallbackToDepencies()
{
	const auto WhyAttributeSet = CastChecked<UWhyAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		WhyAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		WhyAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}
