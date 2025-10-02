// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/AN_SendTargetGroup.h"
#include "AbilitySystemBlueprintLibrary.h"

void UAN_SendTargetGroup::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!MeshComp) return;
	if (TargetSocketName.Num() <= 0) return;

	if (!MeshComp->GetOwner() || !UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(MeshComp->GetOwner()))
	{
		return;
	}

	FGameplayEventData Data;

	for (int i = 1; i < TargetSocketName.Num(); ++i)
	{
		FGameplayAbilityTargetData_LocationInfo*  LocationInfo = new FGameplayAbilityTargetData_LocationInfo();

		FVector StartLoc = MeshComp->GetSocketLocation(TargetSocketName[i - 1]);
		FVector EndLoc = MeshComp->GetSocketLocation(TargetSocketName[i]);

		LocationInfo->SourceLocation.LiteralTransform.SetLocation(StartLoc);
		LocationInfo->TargetLocation.LiteralTransform.SetLocation(EndLoc);

		Data.TargetData.Add(LocationInfo);
	}
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(), EventTag, Data);
}

