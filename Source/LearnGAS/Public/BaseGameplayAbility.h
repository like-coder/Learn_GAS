// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BaseGameplayAbility.generated.h"

//技能消耗类型
UENUM(BlueprintType)
enum class ECostType : uint8
{
	HP,
	MP,
	Strength
};

USTRUCT(BlueprintType)
struct FGameplayAbilityInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
	float CD;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
	ECostType CostType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
	float CostValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
	UMaterialInstance* IconMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
	TSubclassOf<UBaseGameplayAbility> AbilityClass;

	FGameplayAbilityInfo() :
		CD(0), CostType(ECostType::MP), CostValue(0), IconMaterial(nullptr), AbilityClass(nullptr) {}

	FGameplayAbilityInfo(float CD, ECostType CostType, float CostValue, UMaterialInstance* IconMaterial, TSubclassOf<UBaseGameplayAbility> AbilityClass)
	{
		this->CD = CD;
		this->CostType = CostType;
		this->CostValue = CostValue;
		this->IconMaterial = IconMaterial;
		this->AbilityClass = AbilityClass;
	}
};

UCLASS()
class LEARNGAS_API UBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "AbilityInfo")
	FGameplayAbilityInfo GetAbilityInfo(int level);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
	UMaterialInstance* IconMaterial;
};
