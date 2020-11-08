// Fill out your copyright notice in the Description page of Project Settings.


#include "SteppingStonePuzzle.h"
#include "PuzzleDungeon/PuzzleDungeonUtilities.h"

// Sets default values
ASteppingStonePuzzle::ASteppingStonePuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;	
}

// Called when the game starts or when spawned
void ASteppingStonePuzzle::BeginPlay()
{
	Super::BeginPlay();
	
	UPuzzleDungeonUtilities::AddStaticMeshGrid(this, RootComponent, StaticMesh, "Mesh", 4, 4, 210.0f, 210.0f);
}

// Called every frame
void ASteppingStonePuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASteppingStonePuzzle::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	UPuzzleDungeonUtilities::AddStaticMeshGrid(this, RootComponent, StaticMesh, "Mesh", 4, 4, 210.0f, 210.0f);
}

