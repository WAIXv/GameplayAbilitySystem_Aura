// 

#pragma once

#include "CoreMinimal.h"
#include "WhyCharacterBase.h"
#include "WhyCharacter.generated.h"

class UMotionWarpingComponent;

UCLASS()
class AURA_API AWhyCharacter : public AWhyCharacterBase
{
	GENERATED_BODY()

public:
	AWhyCharacter();
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	//~ Combat Interface
	virtual int32 GetPlayerLevel() override;
	virtual void SetFacingTarget(FVector FacingTarget) override;
	//~ End Combat Interface

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UMotionWarpingComponent> MotionWarpingComponent;

private:
	virtual  void InitAbilityActorInfo() override;
};
