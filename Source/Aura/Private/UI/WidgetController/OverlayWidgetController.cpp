// 


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/WhyAttributeSet.h"

void UOverlayWidgetController::BroadcastInitValues()
{
	const auto WhyAttributeSet = CastChecked<UWhyAttributeSet>(AttributeSet);
	
	OnHealthChanged.Broadcast(WhyAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(WhyAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(WhyAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(WhyAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbackToDepencies()
{
	const auto WhyAttributeSet = CastChecked<UWhyAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		WhyAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		WhyAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		WhyAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		WhyAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}


