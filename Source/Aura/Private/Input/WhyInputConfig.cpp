// 


#include "Input/WhyInputConfig.h"
const UInputAction* UWhyInputConfig::FindAbilityInputActionForTag(const FGameplayTag& Tag, bool bLogNotFound)
{
	for (const auto& Action : AbilityInputActions)
	{
		if (Action.InputTag.MatchesTagExact(Tag))
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find Info for InputTag [%s] on AbilityInputActions [%s]."), *Tag.ToString(), *GetNameSafe(this))
	}
	return nullptr;
}
