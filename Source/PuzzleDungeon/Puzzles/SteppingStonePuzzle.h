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

	UPROPERTY(EditAnywhere, Category = "Customization")
	UStaticMesh* StaticMesh;
};
