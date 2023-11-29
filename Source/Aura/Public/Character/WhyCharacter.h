// 

#pragma once

#include "CoreMinimal.h"
#include "WhyCharacterBase.h"
#include "WhyCharacter.generated.h"

UCLASS()
class AURA_API AWhyCharacter : public AWhyCharacterBase
{
	GENERATED_BODY()

public:
	AWhyCharacter();
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

private:
	virtual  void InitAbilityActorInfo() override;
};
