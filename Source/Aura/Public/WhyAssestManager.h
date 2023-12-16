// 

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "WhyAssestManager.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UWhyAssestManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	static UWhyAssestManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
