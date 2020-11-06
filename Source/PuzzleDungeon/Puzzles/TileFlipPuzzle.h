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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customization")
	UStaticMesh* TileMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customization")
	int Rows;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customization")
	int Columns;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customization")
	TArray<UStaticMeshComponent*> Tiles;

	UFUNCTION(BlueprintCallable)
	void FlipTiles(UStaticMeshComponent* ClickedTile);

private:

	
};
