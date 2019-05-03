// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSGameState.h"
#include "FPSPlayerController.h"
#include "Engine/World.h"

void AFPSGameState::MultiCastOnMissionComplete_Implementation(APawn* InstigatorPawn, bool bIsMissionSuccess)
{
	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; It++)
	{
		APawn* Pawn = It->Get();
		if (Pawn->IsLocallyControlled())
		{
			Pawn->DisableInput(nullptr);
		}
	}

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
	{
		AFPSPlayerController* PC = Cast<AFPSPlayerController>(It->Get());
		if (PC && PC->IsLocalController())
		{
			PC->OnMissionCompleted(InstigatorPawn, bIsMissionSuccess);
		//	APawn* MyPawn = PC->GetPawn();
		//	if (MyPawn)
		//	{
		//		MyPawn->DisableInput(PC);
		//	}
		}
	}
}
