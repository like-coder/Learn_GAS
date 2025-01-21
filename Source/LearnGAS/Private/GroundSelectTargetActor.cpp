// Fill out your copyright notice in the Description page of Project Settings.


#include "GroundSelectTargetActor.h"
#include "Engine/OverlapResult.h"

void AGroundSelectTargetActor::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);
	PrimaryPC = Cast<APlayerController>(Ability->GetOwningActorFromActorInfo()->GetInstigatorController());
}

void AGroundSelectTargetActor::ConfirmTargetingAndContinue()
{
	//Super::ConfirmTargetingAndContinue();
	FVector LookPoint;
	GetPlayerLookAtPoint(LookPoint);
	TArray<FOverlapResult> OverlapResults;
	TArray<TWeakObjectPtr<AActor>> OverlapActors;

	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = false;		//是否开启复杂碰撞
	QueryParams.bReturnPhysicalMaterial = false;	//是否返回物理材质
	APawn* SelfPawn = PrimaryPC->GetPawn();
	if (SelfPawn->IsValidLowLevel())
	{
		QueryParams.AddIgnoredActor(SelfPawn);
	}

	bool bHit = GetWorld()->OverlapMultiByObjectType(OverlapResults, LookPoint,
		FQuat::Identity, FCollisionObjectQueryParams(ECollisionChannel::ECC_Pawn), 
		FCollisionShape::MakeSphere(SelectRadius), QueryParams);
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
	FGameplayAbilityTargetData_LocationInfo* CenterLoc = new FGameplayAbilityTargetData_LocationInfo();
	CenterLoc->TargetLocation.LiteralTransform = FTransform(LookPoint);
	CenterLoc->TargetLocation.LocationType = EGameplayAbilityTargetingLocationType::LiteralTransform;
	//0号负载
	TargetDataHandle.Add(CenterLoc);

	if (OverlapActors.Num() > 0)
	{
		FGameplayAbilityTargetData_ActorArray* ActorArray = new FGameplayAbilityTargetData_ActorArray();
		ActorArray->SetActors(OverlapActors);
		//1号负载
		TargetDataHandle.Add(ActorArray);
	}

	check(ShouldProduceTargetData());
	if (IsConfirmTargetingAllowed())
	{
		TargetDataReadyDelegate.Broadcast(TargetDataHandle);
	}
}

bool AGroundSelectTargetActor::GetPlayerLookAtPoint(FVector& Out_LookPoint)
{
	FVector ViewLoc;
	FRotator ViewRot;
	PrimaryPC->GetPlayerViewPoint(ViewLoc, ViewRot);

	FHitResult Hit;
	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = true;
	APawn* SelfPawn = PrimaryPC->GetPawn();
	if (SelfPawn->IsValidLowLevel())
	{
		QueryParams.AddIgnoredActor(SelfPawn);
	}

	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, ViewLoc, 
		ViewLoc + ViewRot.Vector() * 5000.0f, ECollisionChannel::ECC_Visibility, QueryParams);
	if (bHit)
	{
		Out_LookPoint = Hit.ImpactPoint;
	}

	return bHit;
}
