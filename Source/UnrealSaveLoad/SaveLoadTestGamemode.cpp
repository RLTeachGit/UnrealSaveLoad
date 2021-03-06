// Fill out your copyright notice in the Description page of Project Settings.



#include "SaveLoadTestGamemode.h"

ASaveLoadTestGamemode::ASaveLoadTestGamemode() : AGameMode()
{
	UE_LOG(LogTemp, Warning, TEXT("Built " __DATE__ " at " __TIME__));

	//Use our player controller
	PlayerControllerClass = ANoMouseLookPlayerController::StaticClass();

	//Use our Pawn
	DefaultPawnClass = AStaticPawn::StaticClass();

	AdvancedSaveLoadGame = NewObject<UAdvancedSaveLoad>(); //Add Save Load code


	SaveLoadWithColour = NewObject<USaveLoadWithColour>();	//Colour Save routine

}



void ASaveLoadTestGamemode::SpawnObjectTest()
{
	FVector	tStartLocation(FMath::FRandRange(XMin, XMax), FMath::FRandRange(YMin, YMax), FMath::FRandRange(ZMin, ZMax));
	FRotator tRotator = FRotator(FMath::FRandRange(0, 360), FMath::FRandRange(0, 360), FMath::FRandRange(0, 360));
	SpawnMyActor(tStartLocation, tRotator);
}

//Remove from scene
void ASaveLoadTestGamemode::OnSpawnableActorDestroy(ASpawnableActor *vActor)
{
	mActorArray.Remove(vActor);
}

//Remove all from scene
void ASaveLoadTestGamemode::ClearMyGame()
{
    while(mActorArray.Num()>0)
    {
        ASpawnableActor* tActor = mActorArray.Top();
        mActorArray.Remove(tActor);
        tActor->Destroy();
    }
}

void ASaveLoadTestGamemode::ClearMyGameNoArray()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnableActor::StaticClass(), FoundActors);
	while (FoundActors.Num() > 0)
	{
		AActor* tActor = FoundActors.Top();
		FoundActors.Remove(tActor);
		tActor->Destroy();
	}
}




//Span a new actor at location
ASpawnableActor*    ASaveLoadTestGamemode::SpawnMyActor(const FVector& Position, const FRotator& Rotation)
{
    FActorSpawnParameters tSpawnParams;
    tSpawnParams.Owner = this;
    tSpawnParams.Instigator = Instigator;
    ASpawnableActor *tSpawn = GetWorld()->SpawnActor<ASpawnableActor>(mBaseObject,Position, Rotation, tSpawnParams);
	FLinearColor tColour(FMath::RandRange(0.0f, 1.0f), FMath::RandRange(0.0f, 1.0f), FMath::RandRange(0.0f, 1.0f));
	tSpawn->SetColour(tColour);
    mActorArray.Add(tSpawn);
    return  tSpawn;
}



void ASaveLoadTestGamemode::AdvancedSaveGame()
{
    int32   tTest=1234;
    AdvancedSaveLoadGame->SaveGame(tTest,this);
}



void ASaveLoadTestGamemode::AdvancedLoadGame()
{
    int32   tTest=-1;
    AdvancedSaveLoadGame->LoadGame(tTest,this);
}



//Simple Load

void ASaveLoadTestGamemode::BasicLoadGame()
{
	FActorSpawnParameters tSpawnParams;
	tSpawnParams.Owner = this;
	tSpawnParams.Instigator = Instigator;
	UBasicSaveLoad* LoadGameInstance = Cast<UBasicSaveLoad>(UGameplayStatics::CreateSaveGameObject(UBasicSaveLoad::StaticClass()));
	LoadGameInstance = Cast<UBasicSaveLoad>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
	FString PlayerNameToDisplay = LoadGameInstance->PlayerName;
	for (FBasicSaveObject tObject : LoadGameInstance->SaveObjects)
	{
		ASpawnableActor *tSpawn = GetWorld()->SpawnActor<ASpawnableActor>(mBaseObject, tObject.Position, FRotator::ZeroRotator, tSpawnParams);
		mActorArray.Add(tSpawn);
	}
}

//Simple Save
void ASaveLoadTestGamemode::BasicSaveGame()
{
	UE_LOG(LogTemp, Warning, TEXT("SaveMyGame()"));
	UBasicSaveLoad* SaveGameInstance = Cast<UBasicSaveLoad>(UGameplayStatics::CreateSaveGameObject(UBasicSaveLoad::StaticClass()));
	SaveGameInstance->PlayerName = TEXT("PlayerOne");
    for(ASpawnableActor* tActor : mActorArray)
    {
        FBasicSaveObject tObject;
        tObject.Position=tActor->GetActorLocation();
        SaveGameInstance->SaveObjects.Add(tObject);
    }
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
}



// New version, called from UI


void ASaveLoadTestGamemode::ColourLoadGame()
{
	int32 tVersion = -1; //Invalidate
	SaveLoadWithColour->LoadGame(GetWorld(), mBaseObject);
}

void ASaveLoadTestGamemode::ColourSaveGame(int32 vVersion)
{
	SaveLoadWithColour->SaveGame(vVersion, GetWorld());
}