// Fill out your copyright notice in the Description page of Project Settings.

#include "SaveLoadTestGamemode.h"


ASaveLoadTestGamemode::ASaveLoadTestGamemode() : AGameMode()
{
	UE_LOG(LogTemp, Warning, TEXT("Built " __DATE__ " at " __TIME__));

	//Use our player controller
	PlayerControllerClass = ANoMouseLookPlayerController::StaticClass();

	//Use our Pawn
	DefaultPawnClass = AStaticPawn::StaticClass();

    SaveLoadGame = NewObject<UBasicSaveLoad>();

	//you can set whatever (if any) other default framework classes

}

void ASaveLoadTestGamemode::SpawnObjectTest()
{
	FVector	tStartLocation(FMath::FRandRange(-1000,1000), FMath::FRandRange(-1000, 1000), FMath::FRandRange(70, 200));

	SpawnMyActor(tStartLocation);
}

void ASaveLoadTestGamemode::OnSpawnableActorDestroy(ASpawnableActor *vActor)
{
	mActorArray.Remove(vActor);
}

void ASaveLoadTestGamemode::ClearMyGame()
{
    while(mActorArray.Num()>0)
    {
        ASpawnableActor* tActor = mActorArray.Top();
        mActorArray.Remove(tActor);
        tActor->Destroy();
    }
}


ASpawnableActor*    ASaveLoadTestGamemode::SpawnMyActor(FVector& vPosition)
{
    FActorSpawnParameters tSpawnParams;
    tSpawnParams.Owner = this;
    tSpawnParams.Instigator = Instigator;
    ASpawnableActor *tSpawn = GetWorld()->SpawnActor<ASpawnableActor>(mBaseObject,vPosition,FRotator::ZeroRotator, tSpawnParams);
    mActorArray.Add(tSpawn);
    return  tSpawn;
}

void ASaveLoadTestGamemode::LoadMyGame()
{
    FActorSpawnParameters tSpawnParams;
    tSpawnParams.Owner = this;
    tSpawnParams.Instigator = Instigator;
    USaveGameTest* LoadGameInstance = Cast<USaveGameTest>(UGameplayStatics::CreateSaveGameObject(USaveGameTest::StaticClass()));
    LoadGameInstance = Cast<USaveGameTest>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
    FString PlayerNameToDisplay = LoadGameInstance->PlayerName;
    for(FSaveTestObject tObject : LoadGameInstance->SaveObjects)
    {
        ASpawnableActor *tSpawn = GetWorld()->SpawnActor<ASpawnableActor>(mBaseObject,tObject.Position,FRotator::ZeroRotator, tSpawnParams);
        mActorArray.Add(tSpawn);
    }
}

void ASaveLoadTestGamemode::TestSave()
{
    int32   tTest=1234;
    SaveLoadGame->SaveGame(tTest,this);
}

void ASaveLoadTestGamemode::TestLoad()
{
    int32   tTest=-1;
    SaveLoadGame->LoadGame(tTest,this);
}

void ASaveLoadTestGamemode::SaveMyGame()
{
	UE_LOG(LogTemp, Warning, TEXT("SaveMyGame()"));
	USaveGameTest* SaveGameInstance = Cast<USaveGameTest>(UGameplayStatics::CreateSaveGameObject(USaveGameTest::StaticClass()));
	SaveGameInstance->PlayerName = TEXT("PlayerOne");
    for(ASpawnableActor* tActor : mActorArray)
    {
        FSaveTestObject tObject;
        tObject.Position=tActor->GetActorLocation();
        SaveGameInstance->SaveObjects.Add(tObject);
    }
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
}
