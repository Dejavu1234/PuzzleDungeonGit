// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "PuzzleDungeonPlayerController.h"

APuzzleDungeonPlayerController::APuzzleDungeonPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}
