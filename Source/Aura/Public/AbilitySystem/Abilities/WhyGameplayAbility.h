// 

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "WhyGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UWhyGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FGameplayTag StartUpInputTag;
};
