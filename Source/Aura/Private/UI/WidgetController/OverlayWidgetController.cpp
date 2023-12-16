// 


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/WhyAbilitySystemComponent.h"
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

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(WhyAttributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data) {
			OnHealthChanged.Broadcast(Data.NewValue);
	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(WhyAttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data) {
			OnMaxHealthChanged.Broadcast(Data.NewValue);
	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(WhyAttributeSet->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data) {
			OnManaChanged.Broadcast(Data.NewValue);
	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(WhyAttributeSet->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data) {
			OnMaxManaChanged.Broadcast(Data.NewValue);
	});

	Cast<UWhyAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags) {
			for (const auto& Tag : AssetTags)
			{
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName{"Message"});
				if (Tag.MatchesTag(MessageTag))
				{
					const auto Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					MessageWidgetRowDelegate.Broadcast(*Row);
				}
			}
		});
}

