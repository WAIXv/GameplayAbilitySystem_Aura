// 

#pragma once

#include "CoreMinimal.h"
#include "WhyGameplayAbility.h"
#include "WhyProjectileSpell.generated.h"

class AWhyProjectile;
/**
 * 
 */
UCLASS()
class AURA_API UWhyProjectileSpell : public UWhyGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable)
	void SpawnProjectile(const FVector& ProjectileTargetLocation);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AWhyProjectile> ProjectileClass;
};
