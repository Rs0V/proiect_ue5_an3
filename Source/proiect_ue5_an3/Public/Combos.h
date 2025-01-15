// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Combos.generated.h"


//****************
// PLAYER ATTACKS
//****************
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



//***************
// ENEMY ATTACKS
//***************
USTRUCT(BlueprintType)
struct FEnemyPhase
{
	GENERATED_BODY()

	/**
	 * Time before the attack phase is executed.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float telegraphTime;

	/**
	 * Time allowed for the enemy to retry the attack phase when reengaging the opponent after loosing focus of them.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float reengageTime;

	/**
	 * Time to wait after the phase was executed and before the next phase can be processed.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float waitTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool onGround;

	/**
	 * Does the attack phase deal damage?
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool passive;

	/**
	 * The transition to the next phase is done manually instead of by the timers.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool custom;
	/**
	 * Used when 'custom' property is set to 'true'.
	 * When set to 'true', the attack can transition to the next phase.
	 */
	UPROPERTY(BlueprintReadOnly)
	bool completed;


	FEnemyPhase() :
		telegraphTime(0.5f),
		reengageTime(0.5f),
		waitTime(0.5f),
		onGround(true),
		passive(false),
		custom(false),
		completed(false)
	{}
};


USTRUCT(BlueprintType)
struct FEnemyAttack
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	int currentPhase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FEnemyPhase> phases;

	UPROPERTY(BlueprintReadWrite)
	float telegraphTimer;

	UPROPERTY(BlueprintReadWrite)
	float reengageTimer;

	UPROPERTY(BlueprintReadWrite)
	float waitTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float cooldownTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool canMoveWhileCooldown;


	FEnemyAttack() :
		currentPhase(1),
		phases(),
		telegraphTimer(-1.0f),
		reengageTimer(-1.0f),
		waitTimer(-1.0f),
		cooldownTime(1.0f),
		canMoveWhileCooldown(false)
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
	static bool CheckAttack(const UObject* WorldContextObject, UPARAM(ref) TMap<FString, FAttack> &attacks, FString attackName, int phase = 1, bool conditions = true, bool cancelers = false);

	static bool GoToNextPhase(const UObject* WorldContextObject, FAttack &attack);

	static void ResetAttack(FAttack& attack);

	static bool onGround(const UObject* WorldContextObject);

	static bool inAir(const UObject* WorldContextObject);


	UFUNCTION(BlueprintCallable)
	void CompleteEnemyAttackPhase(UPARAM(ref) TMap<FString, FEnemyAttack>& attacks, FString attackName, int phase);
	
};
