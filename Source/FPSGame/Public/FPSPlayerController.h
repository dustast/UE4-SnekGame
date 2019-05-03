// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPSBlackHole.h"
#include "Engine/World.h"
#include "FPSPlayerController.generated.h"


class AFPSBlackHole;
UCLASS()
class FPSGAME_API AFPSPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	FString CodeSequence;
	float TimeOfLastKeyPress;
	void ResetExpiredCodeSequence();
	void CheckCodeSequence();

public:
		UFUNCTION(BlueprintImplementableEvent,Category="PlayerController")
		void OnMissionCompleted(APawn* InstigatorPawn, bool bIsMissionSuccess);

		virtual bool InputKey(FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad) override;
		
		UPROPERTY(EditDefaultsOnly, Category = "BlackHole")
		TSubclassOf<AFPSBlackHole> BlackClass;
		//ProjectileClass = LoadObjFromPath<UClass>(AssetPath); this is to directly set a class in C++
};
