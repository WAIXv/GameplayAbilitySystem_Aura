// 


#include "WhyAssestManager.h"

#include "WhyGameplayTags.h"

UWhyAssestManager& UWhyAssestManager::Get()
{
	check(GEngine);

	return *Cast<UWhyAssestManager>(GEngine->AssetManager);
}

void UWhyAssestManager::StartInitialLoading()
{
	Super::StartInitialLoading();
}
