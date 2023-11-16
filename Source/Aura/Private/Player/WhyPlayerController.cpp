// 


#include "Player/WhyPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interaction/InteractableInterface.h"

AWhyPlayerController::AWhyPlayerController()
{
	bReplicates = true;
}

void AWhyPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorChase();
}

void AWhyPlayerController::CursorChase()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastInteraction = CurInteraction;
	CurInteraction = Cast<IInteractableInterface>(CursorHit.GetActor());

	/**
	 * 光标射线检测，有几种情况：
	 *	1. Last 为空 && Cur 也为空
	 *		-- Do nothing
	 *	2. Last 为空 && Cur 不为空
	 *		-- 新选中，高亮Cur
	 *	3. Last 不为空 && Cur 不为空
	 *		-- 持续选中
	 *			-- Last == Cur， Do nothing
	 *			-- Last != Cur, 切换高亮
	 *	4. Last 不为空 && Cur 为空
	 *		-- 退出选中，取消高亮
	 */
	
	if (LastInteraction == nullptr)
	{
		if (CurInteraction != nullptr)
		{
			CurInteraction->HighlightActor();
		}
	}
	else
	{
		if (CurInteraction == nullptr)
		{
			LastInteraction->UnHighlightActor();
		}
		else
		{
			if (LastInteraction != CurInteraction)
			{
				LastInteraction->UnHighlightActor();
				CurInteraction->HighlightActor();
			}
		}
	}
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

void AWhyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AWhyPlayerController::Move);
}

void AWhyPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator YawRotation{0.0f, GetControlRotation().Yaw, 0.0f};

	const FVector ForwardDirection = FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix{YawRotation}.GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}


