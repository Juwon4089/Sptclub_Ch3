// Copyright Epic Games, Inc. All Rights Reserved.

#include "Sptclub_Ch3GameMode.h"
#include "Sptclub_Ch3Character.h"
#include "UObject/ConstructorHelpers.h"

ASptclub_Ch3GameMode::ASptclub_Ch3GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
