// Fill out your copyright notice in the Description page of Project Settings.


#include "TileFlipPuzzle.h"

// Sets default values
ATileFlipPuzzle::ATileFlipPuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;	
}

// Called when the game starts or when spawned
void ATileFlipPuzzle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATileFlipPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATileFlipPuzzle::FlipTiles(UStaticMeshComponent* ClickedTile)
{
	int Index = Tiles.Find(ClickedTile);
	if (Index == -1)
	{
		return;
	}

	TArray<int> TilesToFlip = { Index };

	// Above
	TilesToFlip.Add(Index + 1);

	// Below
	TilesToFlip.Add(Index - 1);

	// BottomRight
	TilesToFlip.Add(Index + Columns);

	// TopLeft
	TilesToFlip.Add(Index - Columns);

	TilesToFlip.Add(Index + Columns + 1);
	TilesToFlip.Add(Index + Columns + 2);

	TilesToFlip.Add(Index - Columns - 1);
	TilesToFlip.Add(Index - Columns - 2);

	for (auto itr : TilesToFlip)
	{
		if (itr >= 0 && itr < Tiles.Num())
		{
			Tiles[itr]->AddRelativeRotation(FRotator(0.0f, 0.0f, 180.0f));
		}
	}
}

