
#include "Character/WhyCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/WhyAbilitySystemComponent.h"

AWhyCharacterBase::AWhyCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* AWhyCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AWhyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWhyCharacterBase::InitAbilityActorInfo()
{
}

void AWhyCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level)
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	auto ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const auto SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

void AWhyCharacterBase::InitDefalutAttributes()
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1.f);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1.f);
	
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}

void AWhyCharacterBase::AddCharacterAbilities()
{
	UWhyAbilitySystemComponent* WhyASC = CastChecked<UWhyAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;

	WhyASC->AddCharacterAbilities(StartUpAbilities);
}

