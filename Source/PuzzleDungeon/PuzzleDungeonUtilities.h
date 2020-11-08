// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/PlayerController.h"
#include "PuzzleDungeonUtilities.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEDUNGEON_API UPuzzleDungeonUtilities : public UObject
{
	GENERATED_BODY()
	
public:
	// Exposed Functions

	UFUNCTION(BlueprintCallable, Category = "PuzzleDungeon|Utilities")
	static FHitResult TraceFromMouse(APlayerController* PlayerController, ECollisionChannel CollisionChannel);

	// Other

	// To use this correctly, you should be calling this in OnConstruction, and On BeginPlay
	static TArray<TArray<UStaticMeshComponent*>> AddStaticMeshGrid(UObject* Actor, USceneComponent* ParentComponent, UStaticMesh* Mesh, FString ComponentName, int Rows, int Columns, float HorizontalOffset, float VerticalOffset);
};
