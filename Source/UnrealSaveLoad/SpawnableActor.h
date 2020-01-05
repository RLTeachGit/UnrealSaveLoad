// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnableActor.generated.h"

class   ASaveLoadTestGamemode;

UCLASS()
class UNREALSAVELOAD_API ASpawnableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnableActor();

	//Called when Actor is abotu to go away
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

protected:
	// Called when the Actor starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};
