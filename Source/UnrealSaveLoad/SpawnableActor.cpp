// Fill out your copyright notice in the Description page of Project Settings.



#include "SpawnableActor.h"
#include "SaveLoadTestGamemode.h"
#include "Engine/World.h"


// Sets default values
ASpawnableActor::ASpawnableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASpawnableActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	Cast<ASaveLoadTestGamemode>(GetWorld()->GetAuthGameMode())->OnSpawnableActorDestroy(this);	//Get GameMode to delete ourself from its list of actors
}

// Called when the game starts or when spawned
void ASpawnableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

