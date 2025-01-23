// Fill out your copyright notice in the Description page of Project Settings.


#include "FireBlastTargetActor.h"
#include "Engine/OverlapResult.h"

void AFireBlastTargetActor::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);
	PrimaryPC = Cast<APlayerController>(Ability->GetOwningActorFromActorInfo()->GetInstigatorController());
}

void AFireBlastTargetActor::ConfirmTargetingAndContinue()
{
	APawn* SelfPawn = PrimaryPC->GetPawn();
	if (!SelfPawn->IsValidLowLevel())
	{
		return;
	}

	TArray<FOverlapResult> OverlapResults;
	TArray<TWeakObjectPtr<AActor>> OverlapActors;

	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = false;		//�Ƿ���������ײ
	QueryParams.bReturnPhysicalMaterial = false;	//�Ƿ񷵻��������
	QueryParams.AddIgnoredActor(SelfPawn);

	bool bHit = GetWorld()->OverlapMultiByObjectType(OverlapResults, SelfPawn->GetActorLocation(),
		FQuat::Identity, FCollisionObjectQueryParams(ECollisionChannel::ECC_Pawn),
		FCollisionShape::MakeSphere(AroundRadius), QueryParams);
	if (bHit)
	{
		for (FOverlapResult& OverlapResult : OverlapResults)
		{
			APawn* Enemy = Cast<APawn>(OverlapResult.GetActor());
			if (Enemy->IsValidLowLevel() && !OverlapActors.Contains(Enemy))
			{
				OverlapActors.Add(Enemy);
			}
		}
	}

	FGameplayAbilityTargetDataHandle TargetDataHandle;
	if (OverlapActors.Num() > 0)
	{
		FGameplayAbilityTargetData_ActorArray* ActorArray = new FGameplayAbilityTargetData_ActorArray();
		ActorArray->SetActors(OverlapActors);
		//0�Ÿ���
		TargetDataHandle.Add(ActorArray);
	}

	check(ShouldProduceTargetData());
	if (IsConfirmTargetingAllowed())
	{
		TargetDataReadyDelegate.Broadcast(TargetDataHandle);
	}
}
