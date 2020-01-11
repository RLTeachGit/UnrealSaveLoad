// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

//For Serialisation
#include "Runtime/Core/Public/Serialization/BufferArchive.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"
#include "Runtime/Core/Public/Misc/Paths.h"


#include "Runtime/Core/Public/Serialization/MemoryReader.h"

//So we can spawn the Actor
#include "SpawnableActor.h"

#include "SaveLoadWithColour.generated.h"


/**
 * 
 */
UCLASS()
class UNREALSAVELOAD_API USaveLoadWithColour : public UDataAsset
{
	GENERATED_BODY()

public:
	bool	SaveGame(int32& vVersionNumber, UWorld* vWorld);
	bool    LoadGame(UWorld* vWorld, TSubclassOf<ASpawnableActor>& vBaseActors);

};
