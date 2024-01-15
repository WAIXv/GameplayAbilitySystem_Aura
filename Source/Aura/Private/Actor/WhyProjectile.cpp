// 


#include "Actor/WhyProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


AWhyProjectile::AWhyProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(SphereComp);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	SphereComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovementComp->InitialSpeed = 500.f;
	ProjectileMovementComp->MaxSpeed = 550.f;
	ProjectileMovementComp->ProjectileGravityScale = 0.f;
}

void AWhyProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AWhyProjectile::OnSphereOverlap);
}

void AWhyProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnOverlap(OtherActor);
}

