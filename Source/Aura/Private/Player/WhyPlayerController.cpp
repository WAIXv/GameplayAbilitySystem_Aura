// 


#include "Player/WhyPlayerController.h"

#include "AbilitySystemGlobals.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "WhyGameplayTags.h"
#include "AbilitySystem/WhyAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "Input/WhyInputComponent.h"
#include "Interaction/InteractableInterface.h"

AWhyPlayerController::AWhyPlayerController(): LastInteraction(nullptr), CurInteraction(nullptr)
{
	bReplicates = true;
	SplineComponent = CreateDefaultSubobject<USplineComponent>("Spline");
}

void AWhyPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorChase();
	AutoRun();
}

void AWhyPlayerController::CursorChase()
{
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastInteraction = CurInteraction;
	CurInteraction = Cast<IInteractableInterface>(CursorHit.GetActor());
	
	if (LastInteraction != CurInteraction)
	{
		if (LastInteraction) LastInteraction->UnHighlightActor();
		if (CurInteraction) CurInteraction->HighlightActor();
	}
}

void AWhyPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(WhyInputActionTags::LeftMouseButton))
	{
		bTargeting = CurInteraction != nullptr;
		bAutoRunning = false;
	}
}

void AWhyPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(WhyInputActionTags::LeftMouseButton))
	{
		if (bTargeting)
		{
			if (GetASC()) GetASC()->AbilityInputTagReleased(InputTag);
		}
		else
		{
			const APawn* ControlledPawn = GetPawn();
			if (FollowTime <= ShortPressThreshold)
			{
				if (const auto NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination))
				{
					SplineComponent->ClearSplinePoints();
					for (const auto& PointLocation : NavPath->PathPoints)
					{
						SplineComponent->AddSplinePoint(PointLocation, ESplineCoordinateSpace::World);
					}
					CachedDestination = NavPath->PathPoints.Last();
					bAutoRunning = true;
				}
			}
			FollowTime = 0.f;
			bTargeting = false;
		}
	}
	else
	{
		if (GetASC()) GetASC()->AbilityInputTagReleased(InputTag);
	}
}

void AWhyPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(WhyInputActionTags::LeftMouseButton))
	{
		if (bTargeting)
		{
			if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
		}
		else
		{
			// 鼠标没有指向目标
			FollowTime += GetWorld()->DeltaTimeSeconds;
			
			if (CursorHit.bBlockingHit)
			{
				CachedDestination = CursorHit.ImpactPoint;
			}

			if(APawn* ControlledPawn = GetPawn())
			{
				const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
				ControlledPawn->AddMovementInput(WorldDirection);
			}
		}
	}
	else
	{
		if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
	}
}

UWhyAbilitySystemComponent* AWhyPlayerController::GetASC()
{
	if (WhyAbilitySystemComponent == nullptr)
	{
		WhyAbilitySystemComponent = Cast<UWhyAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(GetPawn<APawn>()));
	}
	return WhyAbilitySystemComponent;
}

void AWhyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(InputMappingContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);

	//TODO : Client为什么不能在这访问到PlayerState
	// if (const auto WhyHUD = GetHUD<AWhyHUD>())
	// {
	// 	const auto WhyPlayerState = GetPlayerState<AWhyPlayerState>();
	// 	WhyHUD->InitOverlay(this, WhyPlayerState, WhyPlayerState->GetAbilitySystemComponent(), WhyPlayerState->GetAttributeSet());
	// }
}

void AWhyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UWhyInputComponent* WhyInputComponent = CastChecked<UWhyInputComponent>(InputComponent);
	WhyInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AWhyPlayerController::Move);
	WhyInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
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

void AWhyPlayerController::AutoRun()
{
	if (!bAutoRunning) return;
	if (APawn* ControlledPawn = GetPawn())
	{
		const FVector LocationOnSpline = SplineComponent->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction = SplineComponent->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);

		const float DistanceToDestination = (CachedDestination - LocationOnSpline).Length();
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}


