// 


#include "Character/WhyEnemy.h"

#include "AbilitySystem/WhyAbilitySystemComponent.h"
#include "AbilitySystem/WhyAttributeSet.h"
#include "Aura/Aura.h"

AWhyEnemy::AWhyEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UWhyAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UWhyAttributeSet>("AttributeSet");
	
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AWhyEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	InitAbilityActorInfo();
}

void AWhyEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UWhyAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
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