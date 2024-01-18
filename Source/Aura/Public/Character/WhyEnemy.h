// 

#pragma once

#include "CoreMinimal.h"
#include "WhyCharacterBase.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Interaction/InteractableInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "WhyEnemy.generated.h"

class UWidgetComponent;

UCLASS()
class AURA_API AWhyEnemy : public AWhyCharacterBase, public IInteractableInterface
{
	
	GENERATED_BODY()

public:
	AWhyEnemy();

	//~ Interactable Interface
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	//~ End Interactable Interface

	//~ Combat Interface
	virtual int32 GetPlayerLevel() override;
	//~ End Combat Interface

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void InitDefalutAttributes() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level {1};
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	ECharacterClass CharacterClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;
};
