// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAttributeSet.h"
#include "GameplayEffectExtension.h"

void UBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHPAttribute())
	{
		SetHP(FMath::Clamp(GetHP(), 0.0, GetMaxHP()));
	}

	if (Data.EvaluatedData.Attribute == GetMPAttribute())
	{
		SetHP(FMath::Clamp(GetHP(), 0.0, GetMaxMP()));
	}

	if (Data.EvaluatedData.Attribute == GetStrengthAttribute())
	{
		SetHP(FMath::Clamp(GetHP(), 0.0, GetMaxStrength()));
	}
}