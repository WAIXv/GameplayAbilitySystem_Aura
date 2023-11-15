
#include "Character/WhyCharacterBase.h"

AWhyCharacterBase::AWhyCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AWhyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

