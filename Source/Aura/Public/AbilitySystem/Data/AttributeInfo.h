// 

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttributeInfo.generated.h"

USTRUCT(BlueprintType)
struct AURA_API FWhyAttributeInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag {};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName {};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeDescirption {};

	UPROPERTY(BlueprintReadOnly)
	float AttributeValue {0.f};
};

/**
 * 
 */
UCLASS()
class AURA_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	FWhyAttributeInfo FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound = false) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FWhyAttributeInfo> AttributeInformation;
};
