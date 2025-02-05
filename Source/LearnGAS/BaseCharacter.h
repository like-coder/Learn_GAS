// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseGameplayAbility.h"
#include "BaseAttributeSet.h"
#include "BaseCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangeEvent, float, NewValue, float, OldValue);

UCLASS()
class LEARNGAS_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnHealthAttributeChanged(const FOnAttributeChangeData& Data);

	void OnMPAttributeChanged(const FOnAttributeChangeData& Data);

	void OnStrengthAttributeChanged(const FOnAttributeChangeData& Data);

	UPROPERTY(BlueprintAssignable, Category = "Ability")
	FOnHealthChangeEvent HPChangeEvent;

	UPROPERTY(BlueprintAssignable, Category = "Ability")
	FOnHealthChangeEvent MPChangeEvent;

	UPROPERTY(BlueprintAssignable, Category = "Ability")
	FOnHealthChangeEvent StrengthChangeEvent;

	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
	FGameplayAbilityInfo GameplayAbilityInfo(TSubclassOf<UBaseGameplayAbility> AbilityClass, int level);
};
