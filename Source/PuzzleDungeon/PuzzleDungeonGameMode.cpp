// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "PuzzleDungeonGameMode.h"
#include "PuzzleDungeonPlayerController.h"
#include "PuzzleDungeonPawn.h"

APuzzleDungeonGameMode::APuzzleDungeonGameMode()
{
	// no pawn by default
	DefaultPawnClass = APuzzleDungeonPawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = APuzzleDungeonPlayerController::StaticClass();
}
