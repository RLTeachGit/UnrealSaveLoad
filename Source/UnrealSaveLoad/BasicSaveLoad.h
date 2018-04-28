// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


class   ASaveLoadTestGamemode;
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

#include "BasicSaveLoad.generated.h"


USTRUCT()
struct  FBasicActorSave
{
    GENERATED_BODY()
    
    UPROPERTY()
    FVector Position;
};


USTRUCT()
struct  FSaveFile
{
    GENERATED_BODY()
    
    UPROPERTY()
    TArray<FBasicActorSave> Actors;
};


//Make as many Unique Overloads as you want!
FORCEINLINE FArchive& operator<<(FArchive &Ar, FBasicActorSave& vActorData )
{
    
    Ar << vActorData.Position;
    
    return Ar;
}

//Make as many Unique Overloads as you want!
FORCEINLINE FArchive& operator<<(FArchive &Ar, FSaveFile& vSaveGameData )
{
    
    Ar << vSaveGameData.Actors;
    
    return Ar;
}



UCLASS()
class UNREALSAVELOAD_API UBasicSaveLoad : public UDataAsset
{
	GENERATED_BODY()
	
private:
    void    SaveLoad(FArchive& vArchive, int32& vVersionNumber,FSaveFile& vSaveFile);
    
public:
    bool    SaveGame(int32& vVersionNumber,ASaveLoadTestGamemode* vGameMode);
    bool    LoadGame(int32& vVersionNumber,ASaveLoadTestGamemode* vGameMode);

};



