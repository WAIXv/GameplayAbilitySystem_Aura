// 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WhyProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class AURA_API AWhyProjectile : public AActor
{
	GENERATED_BODY()

public:
	AWhyProjectile();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComp;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereComp;
	
};
