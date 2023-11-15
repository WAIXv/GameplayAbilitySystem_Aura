// Copyright Druid Mechanics

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WhyCharacterBase.generated.h"

UCLASS(Abstract)
class AURA_API AWhyCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:

	AWhyCharacterBase();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
};
