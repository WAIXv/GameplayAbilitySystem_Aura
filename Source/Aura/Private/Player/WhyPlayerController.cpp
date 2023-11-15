// 


#include "Player/WhyPlayerController.h"

#include "EnhancedInputSubsystems.h"

AWhyPlayerController::AWhyPlayerController()
{
	bReplicates = true;
}

void AWhyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(WhyContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(WhyContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}
