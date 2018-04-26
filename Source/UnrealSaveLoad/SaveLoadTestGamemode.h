// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "NoMouseLookPlayerController.h"
#include "StaticPawn.h"
#include "SpawnableActor.h"
#include "Engine/World.h"

#include "SaveGameTest.h"
#include "Kismet/GameplayStatics.h"

#include "SaveLoadTestGamemode.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSAVELOAD_API ASaveLoadTestGamemode : public AGameMode
{
	GENERATED_BODY()
	ASaveLoadTestGamemode();

public:
	UFUNCTION(BlueprintCallable)
	void	SpawnObjectTest();

	UPROPERTY(EditAnywhere)
	TSubclassOf<ASpawnableActor> mBaseObject;
	

	void	OnSpawnableActorDestroy(ASpawnableActor* vActor);

	UFUNCTION(BlueprintCallable)
	void	SaveMyGame();
    
    UFUNCTION(BlueprintCallable)
    void    LoadMyGame();
    
    UFUNCTION(BlueprintCallable)
    void    ClearMyGame();

private:
	TArray<ASpawnableActor*>	mActorArray;

};
