// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicSaveLoad.h"



void    UBasicSaveLoad::SaveLoad(FArchive& vArchive, int32& vVersionNumber, FSaveFile& vSaveFile)
{
    vArchive << vVersionNumber;
    vArchive << vSaveFile;
}

bool    UBasicSaveLoad::SaveGame(int32& vVersionNumber,ASaveLoadTestGamemode* vGameMode)
{
    FString tFilename=FPaths::ProjectSavedDir() + "\\SaveGame.rl";
    FBufferArchive  ToBinary;
    FSaveFile       tSaveFile;
    for(AActor* tActor : vGameMode->mActorArray)    //Make a temp list of basic Actor restore Data
    {
        FBasicActorSave tActorSave;
        tActorSave.Position=tActor->GetActorLocation();
        tSaveFile.Actors.Add(tActorSave);
    }
    SaveLoad(ToBinary,vVersionNumber,tSaveFile);
    if(ToBinary.Num()>=0)
    {
        if (FFileHelper::SaveArrayToFile(ToBinary, * tFilename))
        {
            // Free Binary Array
            ToBinary.FlushCache();
            ToBinary.Empty();
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Saved: %s"), *tFilename));
            return true;
        }
    }
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Not Saved"));
    return false;
}


bool    UBasicSaveLoad::LoadGame(int32& vVersionNumber,ASaveLoadTestGamemode* vGameMode)
{
    FString tFilename=FPaths::ProjectSavedDir() + "\\SaveGame.rl";
    TArray<uint8> TheBinaryArray;
    if (FFileHelper::LoadFileToArray(TheBinaryArray, *tFilename))
    {
        FActorSpawnParameters tSpawnParams;
        tSpawnParams.Owner = vGameMode;
        tSpawnParams.Instigator = vGameMode->Instigator;
        int32   tBytes=TheBinaryArray.Num();
        if(tBytes >= 0)
        {
            FMemoryReader FromBinary = FMemoryReader(TheBinaryArray, true); //true, free data after done
            FromBinary.Seek(0);
            FSaveFile       tSaveFile;
            int32           tVersionNumber=-1;
            SaveLoad(FromBinary,tVersionNumber,tSaveFile);
            UE_LOG(LogTemp, Warning, TEXT("Version %d"),vVersionNumber);

            
            for(FBasicActorSave tActorSave : tSaveFile.Actors)
            {
                ASpawnableActor *tSpawn = GetWorld()->SpawnActor<ASpawnableActor>(vGameMode->mBaseObject,tActorSave.Position,FRotator::ZeroRotator, tSpawnParams);
                vGameMode->mActorArray.Add(tSpawn);
            }
            
            
            
            FromBinary.FlushCache();
            
            TheBinaryArray.Empty();
            FromBinary.Close();
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Loaded: %s %d bytes Content Version:%d"), *tFilename,tBytes,tVersionNumber));
            
            return true;
        }
    }
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Not Loaded"));
    return  false;
}
