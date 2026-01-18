// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/TargetActor_GroundPick.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GenericTeamAgentInterface.h"
#include "Abilities/GameplayAbility.h"
#include "Crunch/Crunch.h"
#include "Engine/OverlapResult.h"

void ATargetActor_GroundPick::ConfirmTargetingAndContinue()
{
	Super::ConfirmTargetingAndContinue();

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);

	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(TargetTraceRange);

	TArray<FOverlapResult> OverlapResults;
	GetWorld()->OverlapMultiByObjectType(OverlapResults, GetActorLocation(), FQuat::Identity, ObjectQueryParams,
	                                     CollisionShape);
	
	TSet<AActor*> TargetActors;	
	
	IGenericTeamAgentInterface* OwnerTeamInterface = nullptr; 
	
	if (OwnerTeamInterface)
	{
		OwnerTeamInterface = Cast<IGenericTeamAgentInterface>(OwningAbility->GetAvatarActorFromActorInfo());
	}
	
	for (const FOverlapResult& OverlapResult : OverlapResults)
	{
		if (OwnerTeamInterface && OwnerTeamInterface->GetTeamAttitudeTowards(*OverlapResult.GetActor()) == ETeamAttitude::Friendly && !bShouldTargetFriendl)
			continue;
		
		if (OwnerTeamInterface && OwnerTeamInterface->GetTeamAttitudeTowards(*OverlapResult.GetActor()) == ETeamAttitude::Hostile && !bShouldTargetEnemy)
			continue;
		
		TargetActors.Add(OverlapResult.GetActor());
	}
	FGameplayAbilityTargetDataHandle TargetData = UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActorArray(TargetActors.Array(), false);	
	TargetDataReadyDelegate.Broadcast(TargetData);
}

void ATargetActor_GroundPick::SetTargetOptions(bool bTargetFriendly, bool bTargetEnemy)
{
	bShouldTargetFriendl = bTargetFriendly;
	bShouldTargetEnemy = bTargetEnemy;
}

ATargetActor_GroundPick::ATargetActor_GroundPick()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATargetActor_GroundPick::SetTargetAreaRadius(float NewRadius)
{
	TargetTraceRange = NewRadius;
}

void ATargetActor_GroundPick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PrimaryPC && PrimaryPC->IsLocalPlayerController())
	{
		SetActorLocation(GetTargetPoint());
	}
}

FVector ATargetActor_GroundPick::GetTargetPoint() const
{
	if (!PrimaryPC || !PrimaryPC->IsLocalPlayerController())
		return GetActorLocation();

	FHitResult TraceResult;

	FVector ViewLoc;
	FRotator ViewRot;

	PrimaryPC->GetPlayerViewPoint(ViewLoc, ViewRot);

	FVector TraceEnd = ViewLoc + ViewRot.Vector() * TargetTraceRange;
	GetWorld()->LineTraceSingleByChannel(TraceResult, ViewLoc, TraceEnd,
	                                     ECC_Target);

	if (!TraceResult.bBlockingHit)
	{
		GetWorld()->LineTraceSingleByChannel(TraceResult, TraceEnd,
		                                     TraceEnd + FVector::DownVector * TNumericLimits<float>::Max(), ECC_Target);
	}

	if (!TraceResult.bBlockingHit)
	{
		return GetActorLocation();
	}
	return TraceResult.ImpactPoint;
}
