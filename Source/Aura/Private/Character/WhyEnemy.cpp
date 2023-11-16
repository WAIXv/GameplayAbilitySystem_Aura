// 


#include "Character/WhyEnemy.h"

#include "Aura/Aura.h"

AWhyEnemy::AWhyEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
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