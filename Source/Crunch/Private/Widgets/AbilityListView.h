// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ListView.h"
#include "AbilityListView.generated.h"

class UGameplayAbility;
enum class ECAbilityInputID : uint8;
/**
 * 
 */
UCLASS()
class UAbilityListView : public UListView
{
	GENERATED_BODY()
	
public:
	void ConfigureAbility(const TMap<ECAbilityInputID, TSubclassOf<UGameplayAbility>>& Abilities);
private:
	UPROPERTY(EditAnywhere, Category="Data")
	UDataTable* AbilityDataTable;
	
	void AbilityGaugeGenerated(UUserWidget& Widget);
	const struct FAbilityWidgetData* FindWidgetDataForAbility(const TSubclassOf<UGameplayAbility>& AbilityClass) const;
};
