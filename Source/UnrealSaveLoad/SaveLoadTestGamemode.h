// Fill out your copyright notice in the Description page of Project Settings.

#pragma once




#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "NoMouseLookPlayerController.h"
#include "StaticPawn.h"
#include "SpawnableActor.h"
#include "Engine/World.h"

#include "BasicSaveGame.h"
#include "Kismet/GameplayStatics.h"

#include "AdvancedSaveLoad.h"

#include "SaveLoadTestGamemode.generated.h"

class   UBasicSaveLoad;
class	UAdvancedSaveLoad;
class	ASaveLoadTestGamemode;

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
	ASpawnableActor* SpawnMyActor(const FVector& Position,const FRotator& Rotation);

    
	UFUNCTION(BlueprintCallable)
	void	BasicSaveGame();
    
    UFUNCTION(BlueprintCallable)
    void    BasicLoadGame();
    
    UFUNCTION(BlueprintCallable)
    void    ClearMyGame();
    
    UFUNCTION(BlueprintCallable)
    void    AdvancedLoadGame();
    
    UFUNCTION(BlueprintCallable)
    void    AdvancedSaveGame();

    UPROPERTY()
	UAdvancedSaveLoad*  AdvancedSaveLoadGame;


public:
	TArray<ASpawnableActor*>	mActorArray;


private: //Spawn Range
	float	XMin = -200.0;
	float	XMax = 200.0;
	float	YMin = -200.0;
	float	YMax = 200.0;
	float	ZMin = 70.0;
	float	ZMax = 200.0;

};
