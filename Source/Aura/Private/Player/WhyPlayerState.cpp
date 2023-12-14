// 


#include "Player/WhyPlayerState.h"

#include "AbilitySystem/WhyAbilitySystemComponent.h"
#include "AbilitySystem/WhyAttributeSet.h"
#include "Net/UnrealNetwork.h"

AWhyPlayerState::AWhyPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UWhyAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UWhyAttributeSet>("AttributeSet");
	
	NetUpdateFrequency = 100.f;
}

void AWhyPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWhyPlayerState, Level);
}

UAbilitySystemComponent* AWhyPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AWhyPlayerState::OnRep_Level(int32 OldLevel)
{
	
}
