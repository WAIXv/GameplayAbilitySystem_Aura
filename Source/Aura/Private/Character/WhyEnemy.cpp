// 


#include "Character/WhyEnemy.h"

#include "AbilitySystem/WhyAbilitySystemComponent.h"
#include "AbilitySystem/WhyAttributeSet.h"
#include "Aura/Aura.h"
#include "Components/WidgetComponent.h"
#include "UI/WIdget/WhyUserWidget.h"

AWhyEnemy::AWhyEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UWhyAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UWhyAttributeSet>("AttributeSet");

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
	
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AWhyEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();

	if (const auto WhyUserWidget = Cast<UWhyUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		WhyUserWidget->SetWidgetController(this);
	}

	if (const auto WhyAS = Cast<UWhyAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(WhyAS->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data) {
				OnHealthChanged.Broadcast(Data.NewValue);
			});
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(WhyAS->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data) {
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			});

		OnHealthChanged.Broadcast(WhyAS->GetHealth());
		OnMaxHealthChanged.Broadcast(WhyAS->GetMaxHealth());
	}
}

void AWhyEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UWhyAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	InitDefalutAttributes();
}

void AWhyEnemy::HighlightActor()
{
	Weapon->SetRenderCustomDepth(true);
	GetMesh()->SetRenderCustomDepth(true);
}

void AWhyEnemy::UnHighlightActor()
{
	Weapon->SetRenderCustomDepth(false);
	GetMesh()->SetRenderCustomDepth(false);
}

int32 AWhyEnemy::GetPlayerLevel()
{
	return Level;
}
