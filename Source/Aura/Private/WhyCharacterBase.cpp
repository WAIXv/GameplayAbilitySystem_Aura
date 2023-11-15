// Copyright Druid Mechanics


#include "WhyCharacterBase.h"

// Sets default values
AWhyCharacterBase::AWhyCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AWhyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

