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

	UFUNCTION(BlueprintCallable, Category = "PuzzleDungeon|Utilities")
	static FHitResult TraceFromMouse(APlayerController* PlayerController, ECollisionChannel CollisionChannel);


};
