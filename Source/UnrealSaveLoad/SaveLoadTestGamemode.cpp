// Fill out your copyright notice in the Description page of Project Settings.

#include "SaveLoadTestGamemode.h"


ASaveLoadTestGamemode::ASaveLoadTestGamemode() : AGameMode()
{
	UE_LOG(LogTemp, Warning, TEXT("ASaveLoadTestGamemode()"));

	//Use our player controller
	PlayerControllerClass = ANoMouseLookPlayerController::StaticClass();

	//Use our Pawn
	DefaultPawnClass = AStaticPawn::StaticClass();


	//you can set whatever (if any) other default framework classes

}

void ASaveLoadTestGamemode::SpawnObjectTest()
{
	FActorSpawnParameters tSpawnParams;
	tSpawnParams.Owner = this;
	tSpawnParams.Instigator = Instigator;
	FVector	tStartLocation(FMath::FRandRange(-100,100), FMath::FRandRange(-100, 100), FMath::FRandRange(-100, 100));
	FRotator tStartRotation(0, 0, 0);

	ASpawnableActor *tSpawn = GetWorld()->SpawnActor<ASpawnableActor>(mBaseObject,tStartLocation,FRotator::ZeroRotator, tSpawnParams);
	UE_LOG(LogTemp, Warning, TEXT("SpawnObjectTestSanityCheck() %x"),tSpawn);
}
