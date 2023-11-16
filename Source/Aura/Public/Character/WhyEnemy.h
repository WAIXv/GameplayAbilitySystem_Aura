// 

#pragma once

#include "CoreMinimal.h"
#include "WhyCharacterBase.h"
#include "Interaction/InteractableInterface.h"
#include "WhyEnemy.generated.h"

UCLASS()
class AURA_API AWhyEnemy : public AWhyCharacterBase, public IInteractableInterface
{
	
	GENERATED_BODY()

public:
	AWhyEnemy();
	
public:
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
};
