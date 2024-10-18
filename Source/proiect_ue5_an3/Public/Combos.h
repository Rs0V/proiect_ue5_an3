// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Combos.generated.h"


USTRUCT(BlueprintType)
struct FPhase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float waitTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float windowTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool onGround;
	

	FPhase():
		waitTime(0.0f),
		windowTime(0.5f),
		onGround(true)
	{}
};


USTRUCT(BlueprintType)
struct FAttack
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int currentPhase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FPhase> phases;

	UPROPERTY(BlueprintReadWrite)
	float waitTimer;

	UPROPERTY(BlueprintReadWrite)
	float windowTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float resetTime;


	FAttack():
		currentPhase(1),
		phases(),
		waitTimer(-1.0f),
		windowTimer(-1.0f),
		resetTime(0.5f)
	{}
};


/**
 * 
 */
UCLASS()
class PROIECT_UE5_AN3_API UCombos : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable)
	static void UpdateAttacks(float deltaTime, UPARAM(ref) TMap<FString, FAttack> &attacks);
	
	UFUNCTION(BlueprintCallable, meta = (DefaultToSelf = "WorldContextObject"))
	static bool CheckAttack(const UObject* WorldContextObject, UPARAM(ref) TMap<FString, FAttack>& attacks, FString attackName, int phase);

	static bool GoToNextPhase(const UObject* WorldContextObject, FAttack& attack);

	static bool onGround(const UObject* WorldContextObject);

	static bool inAir(const UObject* WorldContextObject);
};
