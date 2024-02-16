// Copyright Epic Games, Inc. All Rights Reserved.


#include "RandGenFPSGameModeBase.h"

ARandGenFPSGameModeBase::ARandGenFPSGameModeBase()
{
	//DefaultPawnClass = ABaseCharacter::StaticClass();
	ConstructorHelpers::FClassFinder<ATestCharacter> PawnClassAsset(TEXT("/Game/Blueprints/TestCharacter_BP"));
	if (PawnClassAsset.Succeeded())
		DefaultPawnClass = PawnClassAsset.Class;
	else
		UE_LOG(LogTemp, Error, TEXT("Failed to read Blueprint test char."));

	//DefaultPawnClass = ATestCharacter::StaticClass();
}