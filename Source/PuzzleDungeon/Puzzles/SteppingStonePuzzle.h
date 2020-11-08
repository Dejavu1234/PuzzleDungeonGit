// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SteppingStonePuzzle.generated.h"

UCLASS()
class PUZZLEDUNGEON_API ASteppingStonePuzzle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASteppingStonePuzzle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(BlueprintCallable)
	bool OnTileClicked(UStaticMeshComponent* Mesh);

	bool CheckPuzzleComplete();

	UFUNCTION(BlueprintCallable)
	UStaticMeshComponent* GetTile(FVector2D Index);	

	UPROPERTY(EditAnywhere, Category = "Customization")
	UStaticMesh* StaticMesh;

	UPROPERTY(EditAnywhere, Category = "Customization")
	int Rows;

	UPROPERTY(EditAnywhere, Category = "Customization")
	int Columns;

	UPROPERTY(EditAnywhere, Category = "Customization")
	bool bRecordingPuzzle;

	UPROPERTY(BlueprintReadWrite)
	int Clicks;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Customization")
	TArray<FVector2D> PuzzleConfig;
		
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPuzzleComplete, bool, Success, float, Score);
	UPROPERTY(BlueprintAssignable)
	FOnPuzzleComplete OnPuzzleComplete;

private:
	TArray<TArray<UStaticMeshComponent*>> TileArray;
	TArray<bool> TileClicked;
	int IsIndexOnPath(FVector2D index);
};
