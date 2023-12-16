// 


#include "Character/WhyCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/WhyAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/WhyPlayerController.h"
#include "Player/WhyPlayerState.h"
#include "UI/HUD/WhyHUD.h"

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
	AddCharacterAbilities();
}

void AWhyCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	// Init ability Actor info for client
	InitAbilityActorInfo();
}

int32 AWhyCharacter::GetPlayerLevel()
{
	const auto WhyPlayerState = GetPlayerState<AWhyPlayerState>();
	check(WhyPlayerState);
	return WhyPlayerState->GetPlayerLevel();
}

void AWhyCharacter::InitAbilityActorInfo()
{
	const auto WhyPlayerState = GetPlayerState<AWhyPlayerState>();
	check(WhyPlayerState)
	AbilitySystemComponent = WhyPlayerState->GetAbilitySystemComponent();
	AttributeSet = WhyPlayerState->GetAttributeSet();
	AbilitySystemComponent->InitAbilityActorInfo(WhyPlayerState, this);
	Cast<UWhyAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	if (const auto WhyPlayerController = Cast<AWhyPlayerController>(GetController()))
	{
		if (const auto WhyHUD = WhyPlayerController->GetHUD<AWhyHUD>())
		{
			WhyHUD->InitOverlay(WhyPlayerController, WhyPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
	InitDefalutAttributes();
}


