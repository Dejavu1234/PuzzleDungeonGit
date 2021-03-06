// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "TileFlipPuzzle.generated.h"

UCLASS()
class PUZZLEDUNGEON_API ATileFlipPuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileFlipPuzzle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;

	void ConstructTiles();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customization")
	UStaticMesh* TileMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customization")
	int Rows;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customization")
	int Columns;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customization")
	TArray<UStaticMeshComponent*> Tiles;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customization")
	bool bConfiguringPuzzle;

	UFUNCTION(BlueprintCallable)
	void SavePuzzleConfig();
	UFUNCTION(BlueprintCallable)
	void FlipTiles(UStaticMeshComponent* ClickedTile, bool bInstantRotate);
	UFUNCTION(BlueprintImplementableEvent)
    void InterpTileRotation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle Config")
	TArray<FVector2D> PuzzleConfig;

	UPROPERTY(BlueprintReadWrite)
	TArray<UStaticMeshComponent*> TilesToRotate;
	UPROPERTY(BlueprintReadWrite)
	TArray<FRotator> InitialTileRotations;
	UPROPERTY(BlueprintReadWrite)
	TArray<FRotator> TargetTileRotations;
	UPROPERTY(BlueprintReadWrite)
	bool bFlippingTiles;

	UPROPERTY(BlueprintReadWrite)
	int Clicks;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPuzzleComplete, bool, Success, float, Score);
	UPROPERTY(BlueprintAssignable)
	FOnPuzzleComplete OnPuzzleComplete;

	UFUNCTION(BlueprintCallable)
	bool CheckPuzzleComplete();

private:
	TArray<TArray<UStaticMeshComponent*>> TileArray;

	TArray<FVector2D> FlipHistory;	
	void SetupPuzzle();
	void FindTileInArray(int& _x, int& _y, UStaticMeshComponent* Tile);
	bool CheckIfValidIndex(FVector2D index);
	
};
