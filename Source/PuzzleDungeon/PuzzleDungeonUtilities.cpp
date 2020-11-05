// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleDungeonUtilities.h"
#include "Engine/World.h"

FHitResult UPuzzleDungeonUtilities::TraceFromMouse(APlayerController* PlayerController, ECollisionChannel CollisionChannel)
{
	FVector WorldLocation, WorldDirection;
	PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	FHitResult OutHit;
	UWorld* WorldPtr = PlayerController->GetWorld();
	WorldPtr->LineTraceSingleByChannel(OutHit, WorldLocation, WorldLocation + (WorldDirection * 10000.0f), CollisionChannel);

	return OutHit;
}
