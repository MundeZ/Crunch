// Fill out your copyright notice in the Description page of Project Settings.

#include "Widgets/AbilityListView.h"

#include "AbilityGauge.h"
#include "Abilities/GameplayAbility.h"

void UAbilityListView::ConfigureAbility(const TMap<ECAbilityInputID, TSubclassOf<UGameplayAbility>>& Abilities)
{
	OnEntryWidgetGenerated().AddUObject(this, &UAbilityListView::AbilityGaugeGenerated);
	for (const TPair<ECAbilityInputID, TSubclassOf<UGameplayAbility>>& AbilityPair : Abilities)
	{
		AddItem(AbilityPair.Value.GetDefaultObject());
	}
}

void UAbilityListView::AbilityGaugeGenerated(UUserWidget& Widget)
{
	UAbilityGauge* AbilityGauge = Cast<UAbilityGauge>(&Widget);
	
	if (AbilityGauge)
	{
		AbilityGauge->ConfigureWithWidgetData(FindWidgetDataForAbility(AbilityGauge->GetListItem<UGameplayAbility>()->GetClass()));
	}
}

const FAbilityWidgetData* UAbilityListView::FindWidgetDataForAbility(const TSubclassOf<UGameplayAbility>& AbilityClass) const
{
	if(!AbilityClass) return nullptr;
	
	for (auto& AbilityWidgetDataPtr : AbilityDataTable->GetRowMap())
	{
		const FAbilityWidgetData* WidgetData = AbilityDataTable->FindRow<FAbilityWidgetData>(AbilityWidgetDataPtr.Key, "");
		if (WidgetData->AbilityClass == AbilityClass)
		{
			return WidgetData;
		}
	}
	
	return nullptr;
}
