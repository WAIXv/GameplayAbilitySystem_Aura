// 


#include "AbilitySystem/WhyAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "WhyGameplayTags.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

UWhyAttributeSet::UWhyAttributeSet()
{
	/* Primary Attributes */
	TagsToAttributesMap.Add(WhyPrimaryAttributeTags::Strength, GetStrengthAttribute);
	TagsToAttributesMap.Add(WhyPrimaryAttributeTags::Intelligence, GetIntelligenceAttribute);
	TagsToAttributesMap.Add(WhyPrimaryAttributeTags::Resilience, GetResilienceAttribute);
	TagsToAttributesMap.Add(WhyPrimaryAttributeTags::Vigor, GetVigorAttribute);

	/* Secondary Attributes */
	TagsToAttributesMap.Add(WhySecondaryAttributeTags::Armor, GetArmorAttribute);
	TagsToAttributesMap.Add(WhySecondaryAttributeTags::ArmorPenetration, GetArmorPenetrationAttribute);
	TagsToAttributesMap.Add(WhySecondaryAttributeTags::BlockChance, GetBlockChanceAttribute);
	TagsToAttributesMap.Add(WhySecondaryAttributeTags::HealthRegeneration, GetHealthRegenerationAttribute);
	TagsToAttributesMap.Add(WhySecondaryAttributeTags::ManaRegeneration, GetManaRegenerationAttribute);
	TagsToAttributesMap.Add(WhySecondaryAttributeTags::CriticalHitChance, GetCriticalHitChanceAttribute);
	TagsToAttributesMap.Add(WhySecondaryAttributeTags::CriticalHitDamage, GetCriticalHitDamageAttribute);
	TagsToAttributesMap.Add(WhySecondaryAttributeTags::CriticalHitResistance, GetCriticalHitResistanceAttribute);
	TagsToAttributesMap.Add(WhySecondaryAttributeTags::MaxHealth, GetMaxHealthAttribute);
	TagsToAttributesMap.Add(WhySecondaryAttributeTags::MaxMana, GetMaxManaAttribute);

	/* Vital Attributes */
	TagsToAttributesMap.Add(WhyVitalAttributeTags::Health, GetHealthAttribute);
	TagsToAttributesMap.Add(WhyVitalAttributeTags::Mana, GetManaAttribute);
}

void UWhyAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// Primary Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UWhyAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWhyAttributeSet, Resilience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWhyAttributeSet, Vigor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWhyAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);

	// Secondary Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UWhyAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWhyAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWhyAttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWhyAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWhyAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWhyAttributeSet, CriticalHitResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWhyAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWhyAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);

	// Vital Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UWhyAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWhyAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWhyAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UWhyAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

void UWhyAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxHealth());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxMana());
	}
}

void UWhyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0, GetMaxHealth()));
		UE_LOG(LogTemp, Warning, TEXT("Changed Health on %s, Health: %f"), *Props.TargetAvatarActor.GetName(), GetHealth());
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0, GetMaxMana()));
	}
	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		const float LocalIncomingDamage = GetIncomingDamage();
		SetIncomingDamage(0.f);
		if (LocalIncomingDamage > 0.f)
		{
			const float NewHealth = GetHealth() - LocalIncomingDamage;
			SetHealth(FMath::Clamp(GetHealth(), 0, NewHealth));
		}
	}
}

void UWhyAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWhyAttributeSet, Health, OldHealth);
}

void UWhyAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWhyAttributeSet, MaxHealth, OldMaxHealth);
}

void UWhyAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWhyAttributeSet, Strength, OldStrength);
}

void UWhyAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWhyAttributeSet, Intelligence, OldIntelligence);
}

void UWhyAttributeSet::OnRep_Resiience(const FGameplayAttributeData& OldResiience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWhyAttributeSet, Resilience, OldResiience);
}

void UWhyAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWhyAttributeSet, Vigor, OldVigor);
}

void UWhyAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWhyAttributeSet, Armor, OldArmor);
}

void UWhyAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWhyAttributeSet, ArmorPenetration, OldArmorPenetration);
}

void UWhyAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWhyAttributeSet, BlockChance, OldBlockChance);
}

void UWhyAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWhyAttributeSet, CriticalHitChance, OldCriticalHitChance);
}

void UWhyAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWhyAttributeSet, CriticalHitDamage, OldCriticalHitDamage);
}

void UWhyAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWhyAttributeSet, CriticalHitResistance, OldCriticalHitResistance);
}

void UWhyAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWhyAttributeSet, HealthRegeneration, OldHealthRegeneration);
}

void UWhyAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWhyAttributeSet, ManaRegeneration, OldManaRegeneration);
}

void UWhyAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWhyAttributeSet, Mana, OldMana);
}

void UWhyAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UWhyAttributeSet, MaxHealth, OldMaxMana);
}

void UWhyAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props)
{
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo.Get()->AvatarActor.Get();
	if (const auto SourceCharacter = Cast<ACharacter>(Props.SourceAvatarActor))
	{
		Props.SourceCharacter = SourceCharacter;
		Props.SourceController = SourceCharacter->GetController();
	}

	Props.TargetASC = &Data.Target;
	Props.TargetAvatarActor = Props.TargetASC->AbilityActorInfo.Get()->AvatarActor.Get();
	if(const auto TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor))
	{
		Props.TargetCharacter = TargetCharacter;
		Props.TargetController = TargetCharacter->GetController();
	}
}


