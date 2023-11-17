﻿// 


#include "Character/WhyCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/WhyAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/WhyPlayerState.h"

AWhyCharacter::AWhyCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;


	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AWhyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability Actor info for server
	InitAbilityActorInfo();
}

void AWhyCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	// Init ability Actor info for client
	InitAbilityActorInfo();
}

void AWhyCharacter::InitAbilityActorInfo()
{
	const auto MyPlayerState = GetPlayerState<AWhyPlayerState>();
	check(MyPlayerState)
	AbilitySystemComponent = MyPlayerState->GetAbilitySystemComponent();
	AttributeSet = MyPlayerState->GetAttributeSet();
	AbilitySystemComponent->InitAbilityActorInfo(MyPlayerState, this);
}

