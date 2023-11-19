// 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WhyEffectActor.generated.h"

class UGameplayEffect;

UCLASS()
class AURA_API AWhyEffectActor : public AActor
{
	GENERATED_BODY()

public:
	AWhyEffectActor();
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass) const;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
};
