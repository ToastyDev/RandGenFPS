// Copyright Epic Games, Inc. All Rights Reserved.


#include "RandGenFPSGameModeBase.h"

ARandGenFPSGameModeBase::ARandGenFPSGameModeBase()
{
	//DefaultPawnClass = ABaseCharacter::StaticClass();
	DefaultPawnClass = ATestCharacter::StaticClass();
}