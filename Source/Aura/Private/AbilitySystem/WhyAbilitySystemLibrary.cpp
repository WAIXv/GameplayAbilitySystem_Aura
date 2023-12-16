// 


#include "AbilitySystem/WhyAbilitySystemLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "Player/WhyPlayerState.h"
#include "UI/HUD/WhyHUD.h"
#include "UI/WidgetController/WhyWidgetController.h"

UOverlayWidgetController* UWhyAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AWhyHUD* WhyHUD = Cast<AWhyHUD>(PC->GetHUD()))
		{
			AWhyPlayerState* PS = PC->GetPlayerState<AWhyPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams{ PC, PS, ASC, AS };
			return WhyHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* UWhyAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AWhyHUD* WhyHUD = Cast<AWhyHUD>(PC->GetHUD()))
		{
			AWhyPlayerState* PS = PC->GetPlayerState<AWhyPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams{ PC, PS, ASC, AS };
			return WhyHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}
