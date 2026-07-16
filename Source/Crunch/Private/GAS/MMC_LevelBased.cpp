// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/MMC_LevelBased.h"

#include "CAttributeSet.h"
#include "CHeroAttributeSet.h"

UMMC_LevelBased::UMMC_LevelBased()
{
	LevelCaptureDefinition.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	LevelCaptureDefinition.AttributeToCapture = UCHeroAttributeSet::GetLevelAttribute();
	
	RelevantAttributesToCapture.Add(LevelCaptureDefinition);
	
}

float UMMC_LevelBased::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	UAbilitySystemComponent* ASC = Spec.GetContext().GetInstigatorAbilitySystemComponent();
	if (!ASC) return 0.f;
	
	float level = 0;
	FAggregatorEvaluateParameters EvalParameters;
	EvalParameters.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvalParameters.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	GetCapturedAttributeMagnitude(LevelCaptureDefinition, Spec, EvalParameters, level);
	
	bool bFound;
	
	float RateAttributeVal = ASC->GetGameplayAttributeValue(RateAttribute, bFound);
	if (!bFound) return 0.f;
	
	
	return (level - 1) * RateAttributeVal;
}
