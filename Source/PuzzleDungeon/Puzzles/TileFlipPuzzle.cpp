// Fill out your copyright notice in the Description page of Project Settings.


#include "TileFlipPuzzle.h"
#include "Kismet/KismetSystemLibrary.h"

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

	ConstructTiles();
	
	if (!bConfiguringPuzzle)
	{
		SetupPuzzle();
	}	
}

// Called every frame
void ATileFlipPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATileFlipPuzzle::SetupPuzzle()
{
	for (auto itr : PuzzleConfig)
	{
		FlipTiles(TileArray[itr.X][itr.Y], true);
	}
}

void ATileFlipPuzzle::FindTileInArray(int& _x, int& _y, UStaticMeshComponent* Tile)
{
	for (int y = 0; y < Rows; ++y)
	{
		for (int x = 0; x < Columns; ++x)
		{
			if (TileArray[y][x] == Tile)
			{
				_x = x;
				_y = y;
				return;
			}
		}
	}
}

bool ATileFlipPuzzle::CheckIfValidIndex(FVector2D index)
{
	if (index.X >= 0 && index.X < Rows && index.Y >= 0 && index.Y < Columns)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ATileFlipPuzzle::CheckPuzzleComplete()
{
	for (auto Row : TileArray)
	{
		for (auto Column : Row)
		{
			if (Column->GetRelativeRotation().Roll != 0.0f)
			{
				return false;
			}
		}
	}

	return true;
}

void ATileFlipPuzzle::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	ConstructTiles();
}

void ATileFlipPuzzle::ConstructTiles()
{
	for (int y = 0; y < Rows; ++y)
	{
		TArray<UStaticMeshComponent*> TileRow;
		for (int x = 0; x < Columns; ++x)
		{
			UStaticMeshComponent* NewComponent = NewObject<UStaticMeshComponent>(this, NAME_None, RF_Transient);
			NewComponent->AttachTo(RootComponent);
			NewComponent->RegisterComponent();
			NewComponent->SetStaticMesh(TileMesh);
			NewComponent->CreationMethod = EComponentCreationMethod::SimpleConstructionScript;

			FTransform RelativeTransform = FTransform(FVector(x * 205.0f, y * 205.0f, 0.0f));
			NewComponent->SetRelativeTransform(RelativeTransform);

			TileRow.Add(NewComponent);
		}
		TileArray.Add(TileRow);
	}
}

void ATileFlipPuzzle::SavePuzzleConfig()
{
	if (bConfiguringPuzzle)
	{
		PuzzleConfig = FlipHistory;
	}	
}

void ATileFlipPuzzle::FlipTiles(UStaticMeshComponent* ClickedTile, bool bInstantRotate = false)
{
	// Dont allow flipping if we're mid interp of tiles
	if (bFlippingTiles)
	{
		return;
	}

	int x = -1;
	int y = -1;

	// Get the x & y of the tile that was clicked
	FindTileInArray(x, y, ClickedTile);
	if (x == -1 || y == -1)
	{
		return;
	}

	TArray<FVector2D> TileIndices;

	// Add all adjacent to array
	for (int i = -1; i <= 1; ++i)
	{
		for (int j = -1; j <= 1; ++j)
		{
			TileIndices.Add(FVector2D(y + i, x + j));
		}
	}

	// Store a container of valid tiles to be flipped
	TilesToRotate.Empty();
	TargetTileRotations.Empty();
	InitialTileRotations.Empty();
	for (auto Tile : TileIndices)
	{
		// Only flip tiles if they're valid
		if (CheckIfValidIndex(Tile))
		{
			UStaticMeshComponent* TileStaticMesh = TileArray[Tile.X][Tile.Y];		
			TilesToRotate.Add(TileStaticMesh);

			// Store the initial and target rotation for this tile
			InitialTileRotations.Add(TileStaticMesh->GetRelativeRotation());
			if (TileStaticMesh->GetRelativeRotation() == FRotator::ZeroRotator)
			{
				TargetTileRotations.Add(FRotator(0.0f, 0.0f, 180.0f));
			}
			else
			{
				TargetTileRotations.Add(FRotator::ZeroRotator);
			}

			// Apply rotation now if we're doing an instant rotation
			if (bInstantRotate)
			{				
				TileStaticMesh->SetRelativeRotation(TargetTileRotations[TargetTileRotations.Num() - 1]);				
			}
		}
	}	

	if (!bInstantRotate)
	{
		// Call blueprint override function to rotate tiles
		InterpTileRotation();
		bFlippingTiles = true;
	}
	

	// Take note of flip for history
	FlipHistory.Add(FVector2D(x, y));

	// Check if the puzzle has been solved
	if (CheckPuzzleComplete())
	{
		UKismetSystemLibrary::PrintString(GetWorld(), "Puzzle Complete");
	}	
}