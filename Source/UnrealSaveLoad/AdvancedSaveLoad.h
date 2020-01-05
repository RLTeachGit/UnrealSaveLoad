// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Runtime/Core/Public/Serialization/BufferArchive.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"
#include "Runtime/Core/Public/Misc/Paths.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "Runtime/Core/Public/Serialization/MemoryReader.h"
#include "SaveLoadTestGamemode.h"

#include "SpawnableActor.h"

#include "AdvancedSaveLoad.generated.h"

class   UBasicSaveLoad;
class	UAdvancedSaveLoad;
class	ASaveLoadTestGamemode;

//Classes for Saving

USTRUCT()
struct  FAdvancedActorSave
{
	GENERATED_BODY()

	UPROPERTY()
	FVector Position;
	UPROPERTY()
	FRotator Rotation;
};


USTRUCT()
struct  FAdvancedSaveFile
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FAdvancedActorSave> Actors;
};



//Make as many Unique Overloads as you want!
FORCEINLINE FArchive& operator<<(FArchive& Ar, FAdvancedActorSave& vActorData)
{

	Ar << vActorData.Position; //Save/Load Position
	Ar << vActorData.Rotation;	//Save/Load Rotation

	return Ar;
}

//Make as many Unique Overloads as you want!
FORCEINLINE FArchive& operator<<(FArchive& Ar, FAdvancedSaveFile& vSaveGameData)
{

	Ar << vSaveGameData.Actors;

	return Ar;
}




UCLASS()
class UNREALSAVELOAD_API UAdvancedSaveLoad : public UDataAsset
{
	GENERATED_BODY()
private:
	void    SaveLoad(FArchive& vArchive, int32& vVersionNumber, FAdvancedSaveFile& vSaveFile);

public:
	bool    SaveGame(int32& vVersionNumber, ASaveLoadTestGamemode* vGameMode);
	bool    LoadGame(int32& vVersionNumber, ASaveLoadTestGamemode* vGameMode);
};



