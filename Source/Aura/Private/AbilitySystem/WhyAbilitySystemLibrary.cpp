// 


#include "AbilitySystem/WhyAbilitySystemLibrary.h"

#include "..\..\Public\Game\WhyGameModeBase.h"
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

void UWhyAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContext, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	const auto WhyGameMode = Cast<AWhyGameModeBase>(UGameplayStatics::GetGameMode(WorldContext));
	if (!WhyGameMode) return;

	UCharacterClassInfo* ClassClassInfo = WhyGameMode->CharacterClassInfo;
	AActor* AvatarActor = ASC->GetAvatarActor();

	auto MakeContextWithSourceObj = [AvatarActor, ASC] ()->FGameplayEffectContextHandle {
		FGameplayEffectContextHandle EffectContextHandle = ASC->MakeEffectContext();
		EffectContextHandle.AddSourceObject(AvatarActor);
		return EffectContextHandle;
	};
	FGameplayEffectSpecHandle PrimaryAttributeSpecHandle = ASC->MakeOutgoingSpec(ClassClassInfo->GetClassDefaultInfo(CharacterClass).PrimaryAttributes, Level, MakeContextWithSourceObj());
	FGameplayEffectSpecHandle SecondaryAttributeSpecHandle = ASC->MakeOutgoingSpec(WhyGameMode->CharacterClassInfo->SecondaryAttributes, Level, MakeContextWithSourceObj());
	FGameplayEffectSpecHandle VitalAttributeSpecHandle = ASC->MakeOutgoingSpec(WhyGameMode->CharacterClassInfo->VitalAttributes, Level, MakeContextWithSourceObj());
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributeSpecHandle.Data.Get());
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributeSpecHandle.Data.Get());
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributeSpecHandle.Data.Get());
}
