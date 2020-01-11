// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveLoadWithColour.h"

//For debug
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include <EngineGlobals.h>
#include "Kismet/GameplayStatics.h"


bool USaveLoadWithColour::SaveGame(int32& vVersionNumber, UWorld* vWorld)
{
	bool	tSuccess = false;
	FString tFilename = FPaths::ProjectSavedDir() + "ColourSaveGame.rl";

	if (IsValid(vWorld))
	{
		UE_LOG(LogTemp, Warning, TEXT("ColourSaveGame(%s)"),*tFilename);
		FBufferArchive  ToBinary;

		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(vWorld, ASpawnableActor::StaticClass(), FoundActors);

		switch (vVersionNumber)
		{
			case 1:
			{
				ToBinary << vVersionNumber;		//Save out version number
				int32	tActorCount = FoundActors.Num();	//Actor Count
				ToBinary << tActorCount;	//Output Actor Count
				for (AActor* tActor : FoundActors) //Step through Found Actors
				{
					ASpawnableActor* tSpawnableActor = Cast<ASpawnableActor>(tActor); //Get Correct class
					if (IsValid(tSpawnableActor))
					{
						UE_LOG(LogTemp, Log, TEXT("Saving %s Version %d"), *GetNameSafe(tSpawnableActor), vVersionNumber);
						FVector tPosition = tSpawnableActor->GetActorLocation();
						ToBinary << tPosition;
					}
					else
					{
						UE_LOG(LogTemp, Error, TEXT("Wrong Type %s"), *GetNameSafe(tActor));
					}
				}
				tSuccess = FFileHelper::SaveArrayToFile(ToBinary, *tFilename); //Save to disk
			}
			break;

			case 2:
			{
				ToBinary << vVersionNumber;		//Save out version number
				int32	tActorCount = FoundActors.Num();	//Actor Count
				ToBinary << tActorCount;	//Output Actor Count
				for (AActor* tActor : FoundActors) //Step through Found Actors
				{
					ASpawnableActor* tSpawnableActor = Cast<ASpawnableActor>(tActor); //Get Correct class
					if (IsValid(tSpawnableActor))
					{
						UE_LOG(LogTemp, Log, TEXT("Saving %s Version %d"), *GetNameSafe(tSpawnableActor),vVersionNumber);
						FVector tPosition = tSpawnableActor->GetActorLocation();
						FRotator tRotation = tSpawnableActor->GetActorRotation();
						ToBinary << tPosition; //Output Position
						ToBinary << tRotation; //Output Rotation
					}
					else
					{
						UE_LOG(LogTemp, Error, TEXT("Wrong Type %s"), *GetNameSafe(tActor));
					}
				}
				tSuccess = FFileHelper::SaveArrayToFile(ToBinary, *tFilename); //Save to disk
			}
			break;

			case 3:
			{
				ToBinary << vVersionNumber;		//Save out version number
				int32	tActorCount = FoundActors.Num();	//Actor Count
				ToBinary << tActorCount;	//Output Actor Count
				for (AActor* tActor : FoundActors) //Step through Found Actors
				{
					ASpawnableActor* tSpawnableActor = Cast<ASpawnableActor>(tActor); //Get Correct class
					if (IsValid(tSpawnableActor))
					{
						UE_LOG(LogTemp, Log, TEXT("Saving %s Version %d"), *GetNameSafe(tSpawnableActor), vVersionNumber);
						FVector tPosition = tSpawnableActor->GetActorLocation();
						FRotator tRotation = tSpawnableActor->GetActorRotation();
						FLinearColor tColour(1, 1, 0);
						tSpawnableActor->GetColour(tColour); //Get colour from material parameter
						ToBinary << tPosition; //Output Position
						ToBinary << tRotation; //Output Rotation
						ToBinary << tColour; //Output Colour
					}
					else
					{
						UE_LOG(LogTemp, Error, TEXT("Wrong Type %s"), *GetNameSafe(tActor));
					}
				}
				tSuccess = FFileHelper::SaveArrayToFile(ToBinary, *tFilename); //Save to disk
			}
			break;

			default:
				UE_LOG(LogTemp, Error, TEXT("Invalid Version %d"), vVersionNumber);
			break;
		}
		ToBinary.FlushCache();
		ToBinary.Empty();

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ColourSaveGame() invalid GetWorld()"));
	}
	if (tSuccess)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Saved: %s V:%d"), *tFilename,vVersionNumber));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Save Error: %s V:%d"), *tFilename,vVersionNumber));
	}
	return tSuccess;
}

bool USaveLoadWithColour::LoadGame(UWorld* vWorld, TSubclassOf<ASpawnableActor>& vBaseActors)
{
	bool	tSuccess = false;
	int32 tVersion = -1; //Set Invalid
	FString tFilename = FPaths::ProjectSavedDir() + "ColourSaveGame.rl";
	TArray<uint8> BinaryFileArray;
	if (IsValid(vWorld))
	{
		if (FFileHelper::LoadFileToArray(BinaryFileArray, *tFilename)) //Load into RAM
		{
			FMemoryReader FromBinary = FMemoryReader(BinaryFileArray, true); //Read Binary into stream reader, true = free data after done
			FromBinary.Seek(0); //Position at start of stream
			FromBinary << tVersion;	//Load Version Number
			switch (tVersion)
			{
				case	1:
				{
					UE_LOG(LogTemp, Log, TEXT("Loading %s Version %d"), *tFilename, tVersion);
					int32 tActorCount = -1;
					FromBinary << tActorCount;	//Read Actor Count
					while (tActorCount-- > 0)	//Read Actors
					{
						FVector tPosition;
						FromBinary << tPosition;	//Read Actor Position
						ASpawnableActor* tSpawn = vWorld->SpawnActor<ASpawnableActor>(vBaseActors, tPosition, FRotator::ZeroRotator);
						UE_LOG(LogTemp, Log, TEXT("Loaded %s"), *GetNameSafe(tSpawn));
					}
					tSuccess = true;
				}
				break;

				case	2:
				{
					UE_LOG(LogTemp, Log, TEXT("Loading %s Version %d"), *tFilename, tVersion);
					int32 tActorCount = -1;
					FromBinary << tActorCount;	//Read Actor Count
					while (tActorCount-- > 0)	//Read Actors
					{
						FVector tPosition;
						FRotator tRotation;
						FromBinary << tPosition;	//Read Actor Position
						FromBinary << tRotation;	//Read Actor Rotation
						ASpawnableActor* tSpawn = vWorld->SpawnActor<ASpawnableActor>(vBaseActors, tPosition, tRotation);
						UE_LOG(LogTemp, Log, TEXT("Loaded %s"), *GetNameSafe(tSpawn));
						tSuccess = true;
					}
				}
				break;

				case	3:
				{
					UE_LOG(LogTemp, Log, TEXT("Loading %s Version %d"), *tFilename, tVersion);
					int32 tActorCount = -1;
					FromBinary << tActorCount;	//Read Actor Count
					while (tActorCount-- > 0)	//Read Actors
					{
						FVector tPosition;
						FRotator tRotation;
						FLinearColor tColour(1, 1, 0);
						FromBinary << tPosition;	//Read Actor Position
						FromBinary << tRotation;	//Read Actor Rotation
						FromBinary << tColour;	//Read Actor Colour

						ASpawnableActor* tSpawn = vWorld->SpawnActor<ASpawnableActor>(vBaseActors, tPosition, tRotation);

						tSpawn->SetColour(tColour);

						UE_LOG(LogTemp, Log, TEXT("Loaded %s"), *GetNameSafe(tSpawn));
						tSuccess = true;
					}
				}
				break;

				default:
					UE_LOG(LogTemp, Error, TEXT("Invalid Version %d"), tVersion);
				break;
			}
		}
	}
	if (tSuccess)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Loaded: %s V:%d"), *tFilename, tVersion));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Load Error: %s V:%d"), *tFilename, tVersion));
	}
	return tSuccess;
}
