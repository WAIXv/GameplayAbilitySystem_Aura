// 


#include "Actor/WhyEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/WhyAttributeSet.h"
#include "Components/SphereComponent.h"


// Sets default values
AWhyEffectActor::AWhyEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

void AWhyEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (const auto ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		//TODO : Change to apply a Gameplay Effect
		const UWhyAttributeSet* WhyAttributeSet = Cast<UWhyAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UWhyAttributeSet::StaticClass()));

		UWhyAttributeSet* MutableWhyAttributeSet = const_cast<UWhyAttributeSet*>(WhyAttributeSet);
		MutableWhyAttributeSet->SetHealth(WhyAttributeSet->GetHealth() + 25.f);
	}
}

void AWhyEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AWhyEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AWhyEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AWhyEffectActor::EndOverlap);
}

