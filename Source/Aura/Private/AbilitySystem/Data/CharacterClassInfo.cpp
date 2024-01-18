// 


#include "AbilitySystem/Data/CharacterClassInfo.h"
FCharacterDefaultInfo UCharacterClassInfo::GetClassDefaultInfo(ECharacterClass CharacterClass) const
{
	return CharacterClassInfo.FindChecked(CharacterClass);
}
