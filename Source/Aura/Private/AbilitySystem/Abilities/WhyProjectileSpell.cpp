// 


#include "AbilitySystem/Abilities/WhyProjectileSpell.h"

#include "Actor/WhyProjectile.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"

void UWhyProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);


}

void UWhyProjectileSpell::SpawnProjectile()
{
	if (!GetAvatarActorFromActorInfo()->HasAuthority()) return;

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		FTransform SpawnTransform {CombatInterface->GetCombatSocketLocation()};
		auto Projectile = GetWorld()->SpawnActorDeferred<AWhyProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		// TODO:
		
		Projectile->FinishSpawning(SpawnTransform);
	}
}
