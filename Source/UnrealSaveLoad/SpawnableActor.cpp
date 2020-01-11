// Fill out your copyright notice in the Description page of Project Settings.



#include "SpawnableActor.h"

#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "SaveLoadTestGamemode.h"
#include "Engine/World.h"


// Sets default values
ASpawnableActor::ASpawnableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASpawnableActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	Cast<ASaveLoadTestGamemode>(GetWorld()->GetAuthGameMode())->OnSpawnableActorDestroy(this);	//Get GameMode to delete ourself from its list of actors
}

// Called when the game starts or when spawned
void ASpawnableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void    ASpawnableActor::SetColour(FLinearColor& Colour)
{
    TArray<UStaticMeshComponent*> StaticComps;
    GetComponents<UStaticMeshComponent>(StaticComps);
    if (StaticComps.Num() > 0)
    {
        UMaterialInterface* Material = StaticComps[0]->GetMaterial(0);
        if (IsValid(Material))
        {
            UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);
            DynamicMaterial->SetVectorParameterValue("BaseColour", Colour);
            StaticComps[0]->SetMaterial(0, DynamicMaterial);
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("No Material"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("No Mesh"));
    }
}

bool    ASpawnableActor::GetColour(FLinearColor& Colour)
{
    bool tSuccess = false;
    TArray<UStaticMeshComponent*> StaticComps;
    GetComponents<UStaticMeshComponent>(StaticComps);
    if (StaticComps.Num() > 0)
    {
        UMaterialInterface* Material = StaticComps[0]->GetMaterial(0);
        if (IsValid(Material))
        {
            FMaterialParameterInfo tVP;
            tVP.Name = "BaseColour";
            tSuccess = Material->GetVectorParameterValue(tVP, Colour);
            if (!tSuccess)
            {
                UE_LOG(LogTemp, Error, TEXT("Cannot find Colour"));
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("No Material"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("No Mesh"));
    }
    return(tSuccess);
}

