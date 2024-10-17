// Fill out your copyright notice in the Description page of Project Settings.


#include "Combos.h"


void UCombos::UpdateAttacks(float deltaTime, UPARAM(ref) TMap<FString, FAttack> &attacks)
{
	for (auto &attack_kv : attacks) {
		auto &attack = attack_kv.Value;

		if (attack.waitTimer > 0) {
			attack.waitTimer -= deltaTime;
		}
		if (attack.windowTimer > 0) {
			attack.windowTimer -= deltaTime;
		}

		if (attack.windowTimer > -1 and attack.windowTimer < 0) {
			attack.currentPhase = 1;
			attack.waitTimer = -1;
			attack.windowTimer = -1;
		}
	}
}

bool UCombos::CheckAttack(const UObject* WorldContextObject, UPARAM(ref)TMap<FString, FAttack>& attacks, FString attackName, int phase)
{
	auto attack = attacks.Find(attackName);
	if (attack) {
		if (attack->currentPhase != phase) {
			return false;
		}

		if (attack->currentPhase == 1) {
			return GoToNextPhase(WorldContextObject, *attack);
		}

		if (attack->waitTimer > -1 and attack->waitTimer < 0
		and attack->windowTimer > 0) {
			return GoToNextPhase(WorldContextObject, *attack);
		}
	}
	return false;
}

bool UCombos::GoToNextPhase(const UObject* WorldContextObject, FAttack& attack)
{
	if (WorldContextObject) {
		if (attack.currentPhase == attack.phases.Num()) {
			attack.currentPhase = 0;

			FTimerHandle TimerHandle;
			WorldContextObject
				->GetWorld()
				->GetTimerManager()
				.SetTimer(TimerHandle, [&attack](){
					attack.currentPhase = 1;
				}, attack.resetTime, false);

			return true;
		}
		else if (attack.currentPhase > 0) {
			attack.currentPhase++;
			auto &current_phase = attack.phases[attack.currentPhase - 1];

			attack.waitTimer = current_phase.waitTime;
			attack.windowTimer = current_phase.windowTime + current_phase.waitTime;

			return true;
		}
	}
	return false;
}
