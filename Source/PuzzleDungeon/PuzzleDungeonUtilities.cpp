// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleDungeonUtilities.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

FHitResult UPuzzleDungeonUtilities::TraceFromMouse(APlayerController* PlayerController, ECollisionChannel CollisionChannel)
{
	FVector WorldLocation, WorldDirection;
	PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	FHitResult OutHit;
	UWorld* WorldPtr = PlayerController->GetWorld();
	WorldPtr->LineTraceSingleByChannel(OutHit, WorldLocation, WorldLocation + (WorldDirection * 10000.0f), CollisionChannel);

	return OutHit;
}

TArray<TArray<UStaticMeshComponent*>> UPuzzleDungeonUtilities::AddStaticMeshGrid(UObject* Actor, USceneComponent* ParentComponent, UStaticMesh* Mesh, FString ComponentName, int Rows, int Columns, float HorizontalOffset, float VerticalOffset)
{
	TArray<TArray<UStaticMeshComponent*>> StaticMeshGrid;
	for (int y = 0; y < Rows; ++y)
	{
		TArray<UStaticMeshComponent*> StaticMeshRow;
		for (int x = 0; x < Columns; ++x)
		{
			FName NewName = *(ComponentName + "_" + FString::FromInt(x) + "_" + FString::FromInt(y));
			UStaticMeshComponent* NewComponent = NewObject<UStaticMeshComponent>(Actor, NewName, RF_Transient);
			NewComponent->AttachTo(ParentComponent);
			NewComponent->RegisterComponent();
			NewComponent->SetStaticMesh(Mesh);
			NewComponent->CreationMethod = EComponentCreationMethod::SimpleConstructionScript;

			FTransform RelativeTransform = FTransform(FVector(x * HorizontalOffset, y * VerticalOffset, 0.0f));
			NewComponent->SetRelativeTransform(RelativeTransform);

			StaticMeshRow.Add(NewComponent);
		}
		StaticMeshGrid.Add(StaticMeshRow);
	}

	return StaticMeshGrid;
}

void UPuzzleDungeonUtilities::GetStaticMeshIndex(int& _x, int& _y, int Rows, int Columns, UStaticMeshComponent* StaticMesh, TArray<TArray<UStaticMeshComponent*>> Container)
{
	for (int y = 0; y < Rows; ++y)
	{
		for (int x = 0; x < Columns; ++x)
		{
			if (Container[y][x] == StaticMesh)
			{
				_x = x;
				_y = y;
				return;
			}
		}
	}
}
