// Fill out your copyright notice in the Description page of Project Settings.

#include "StaticPawn.h"
#include "Engine/World.h"

// Sets default values
AStaticPawn::AStaticPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UE_LOG(LogTemp, Warning, TEXT("AStaticPawn()"));
}

// Called when the game starts or when spawned
void AStaticPawn::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetFirstPlayerController()->Possess(this);
	UE_LOG(LogTemp, Warning, TEXT("AStaticPawn::BeginPlay()"));

}

// Called every frame
void AStaticPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AStaticPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

