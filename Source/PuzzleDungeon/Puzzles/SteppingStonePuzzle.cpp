// Fill out your copyright notice in the Description page of Project Settings.


#include "SteppingStonePuzzle.h"
#include "PuzzleDungeon/PuzzleDungeonUtilities.h"
#include "Kismet/KismetSystemLibrary.h"

#include <algorithm>

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
	
	TileArray = UPuzzleDungeonUtilities::AddStaticMeshGrid(this, RootComponent, StaticMesh, "Mesh", Rows, Columns, 210.0f, 210.0f);
	TileClicked.InsertUninitialized(0, PuzzleConfig.Num());

	if (bRecordingPuzzle)
	{
		PuzzleConfig.Empty();
	}
}

// Called every frame
void ASteppingStonePuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASteppingStonePuzzle::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	TileArray = UPuzzleDungeonUtilities::AddStaticMeshGrid(this, RootComponent, StaticMesh, "Mesh", Rows, Columns, 210.0f, 210.0f);
}

bool ASteppingStonePuzzle::OnTileClicked(UStaticMeshComponent* Mesh)
{
	int x = 0;
	int y = 0;
	UPuzzleDungeonUtilities::GetStaticMeshIndex(x, y, Rows, Columns, Mesh, TileArray);

	Clicks++;

	if (bRecordingPuzzle)
	{
		PuzzleConfig.Add(FVector2D(x, y));
	}
	else
	{
		int32 Index = IsIndexOnPath(FVector2D(x, y));
		if (Index != -1)
		{
			TileClicked[Index] = true;
			if (CheckPuzzleComplete())
			{
				OnPuzzleComplete.Broadcast(true, Clicks - PuzzleConfig.Num());
			}
			return true;
		}
		else
		{
			OnPuzzleComplete.Broadcast(false, Clicks - PuzzleConfig.Num());
			return false;
		}
	}

	return true;
}

bool ASteppingStonePuzzle::CheckPuzzleComplete()
{
	for (auto itr : TileClicked)
	{
		if (!itr)
		{
			return false;
		}
	}
	return true;
}

UStaticMeshComponent* ASteppingStonePuzzle::GetTile(FVector2D Index)
{
	return TileArray[Index.Y][Index.X];
}

int ASteppingStonePuzzle::IsIndexOnPath(FVector2D index)
{
	for (int i = 0; i < PuzzleConfig.Num(); ++i)
	{
		if (PuzzleConfig[i] == index)
		{
			return i;
		}
	}
	return -1;
}
