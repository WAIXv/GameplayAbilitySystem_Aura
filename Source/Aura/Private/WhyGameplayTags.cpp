#include "WhyGameplayTags.h"

namespace WhySecondaryAttributeTags
{
	UE_DEFINE_GAMEPLAY_TAG(Armor, FName{TEXTVIEW("Attributes.Secondary.Armor")})
	UE_DEFINE_GAMEPLAY_TAG(ArmorPenetration, FName{TEXTVIEW("Attributes.Secondary.ArmorPenetration")})
	UE_DEFINE_GAMEPLAY_TAG(BlockChance, FName{TEXTVIEW("Attributes.Secondary.BlockChance")})
	UE_DEFINE_GAMEPLAY_TAG(CriticalHitChance, FName{TEXTVIEW("Attributes.Secondary.CriticalHitChance")})
	UE_DEFINE_GAMEPLAY_TAG(CriticalHitDamage, FName{TEXTVIEW("Attributes.Secondary.CriticalHitDamage")})
	UE_DEFINE_GAMEPLAY_TAG(CriticalHitResistance, FName{TEXTVIEW("Attributes.Secondary.CriticalHitResistance")})
	UE_DEFINE_GAMEPLAY_TAG(HealthRegeneration, FName{TEXTVIEW("Attributes.Secondary.HealthRegeneration")})
	UE_DEFINE_GAMEPLAY_TAG(ManaRegeneration, FName{TEXTVIEW("Attributes.Secondary.ManaRegeneration")})
	UE_DEFINE_GAMEPLAY_TAG(MaxHealth, FName{TEXTVIEW("Attributes.Secondary.MaxHealth")})
	UE_DEFINE_GAMEPLAY_TAG(MaxMana, FName{TEXTVIEW("Attributes.Secondary.MaxMana")})
}

namespace WhyPrimaryAttributeTags
{
	UE_DEFINE_GAMEPLAY_TAG(Strength, FName{TEXTVIEW("Attributes.Primary.Strength")})
	UE_DEFINE_GAMEPLAY_TAG(Intelligence, FName{TEXTVIEW("Attributes.Primary.Intelligence")})
	UE_DEFINE_GAMEPLAY_TAG(Resilience, FName{TEXTVIEW("Attributes.Primary.Resilience")})
	UE_DEFINE_GAMEPLAY_TAG(Vigor, FName{TEXTVIEW("Attributes.Primary.Vigor")})
}

namespace WhyVitalAttributeTags
{
	UE_DEFINE_GAMEPLAY_TAG(Health, FName{TEXTVIEW("Attributes.Vital.Health")})
	UE_DEFINE_GAMEPLAY_TAG(Mana, FName{TEXTVIEW("Attributes.Vital.Mana")})
}

namespace WhyInputActionTags
{
	UE_DEFINE_GAMEPLAY_TAG(LeftMouseButton, FName{TEXTVIEW("InputTag.LeftMouseButton")});
	UE_DEFINE_GAMEPLAY_TAG(RightMouseButton, FName{TEXTVIEW("InputTag.RightMouseButton")});
	UE_DEFINE_GAMEPLAY_TAG(Input_1, FName{TEXTVIEW("InputTag.Input_1")});
	UE_DEFINE_GAMEPLAY_TAG(Input_2, FName{TEXTVIEW("InputTag.Input_2")});
	UE_DEFINE_GAMEPLAY_TAG(Input_3, FName{TEXTVIEW("InputTag.Input_3")});
	UE_DEFINE_GAMEPLAY_TAG(Input_4, FName{TEXTVIEW("InputTag.Input_4")});
}

namespace WhyDamageTags
{
	UE_DEFINE_GAMEPLAY_TAG(Damage, FName{TEXTVIEW("Damage")})
}