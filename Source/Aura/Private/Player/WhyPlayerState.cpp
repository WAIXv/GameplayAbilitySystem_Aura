// 


#include "Player/WhyPlayerState.h"

#include "AbilitySystem/WhyAbilitySystemComponent.h"
#include "AbilitySystem/WhyAttributeSet.h"

AWhyPlayerState::AWhyPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UWhyAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UWhyAttributeSet>("AttributeSet");
	
	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* AWhyPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
