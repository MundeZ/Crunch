// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Actor.h"
#include "MinionBarrack.generated.h"

UCLASS()
class AMinionBarrack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMinionBarrack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Spawn")
	FGenericTeamId BarrackTeamID;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	int MinionPerGroup = 3;
	
	UPROPERTY(EditAnywhere, Category = "Spawn")
	float GroupSpawnInterval = 5.f;
	
	UPROPERTY()
	TArray<class AMinion*> MinionPool;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	AActor* Goal;
	
	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<class AMinion> MinionClass;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	TArray<class APlayerStart*> SpawnSpot;

	int NextSpawnSpotIndex = -1;
	
	const APlayerStart* GetNextSpawnSpot();

	void SpawnNewGroup();
	void SpawnNewMinions(int Amount);
	AMinion* GetNextAvailableMinion() const;
	
	FTimerHandle SpawnIntervalTimerHandler;
};
