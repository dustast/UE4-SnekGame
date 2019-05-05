// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSPlayerController.h"
#include "FPSBlackHole.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

bool AFPSPlayerController::InputKey(FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad)
{
	

	     // Only bother with presses (not releases) and don't worry about mouse button events
     if (EventType == EInputEvent::IE_Pressed)
     {
         // Clear the CodeSequence string if the last key press was more than 1 seconds ago
         ResetExpiredCodeSequence();  // in case it's not clear, this is another custom function
 
         // float TimeOfLastKeyPress is a float variable that you'll also set up in your Player Controller class
         TimeOfLastKeyPress = GetGameTimeSinceCreation();  // set the time (now) for the current key press; this is used by ResetExpiredCodeSequence(), above
 
         // Add the pressed key's "character" to the CodeSequence (by getting the key's string representation)
         CodeSequence += Key.ToString();
     
         // Call a custom function that compares the sequence to a list of your matching 'codes'
         CheckCodeSequence();
     }
     
     
	 // Return a bool by calling the Super version of this function
	 return Super::InputKey(Key, EventType, AmountDepressed, bGamepad);

 }
 
void AFPSPlayerController::ResetExpiredCodeSequence()
{
	// Find out how many seconds has passed since the last key press
	float TimeSinceLastKeyPress = GetGameTimeSinceCreation() - TimeOfLastKeyPress;

	bool bSequenceExpired = TimeSinceLastKeyPress > 0.75f;  // 1 second till reset
	if (bSequenceExpired)
	{
		// If more than 1 seconds has passed since the last key press, reset the string; otherwise, don't do anything
		CodeSequence = "";    // reset the string back to a blank, empty string
	}
}


void AFPSPlayerController::CheckCodeSequence()
{
	if (CodeSequence == "EZGAME")
	{
		UE_LOG(LogTemp, Warning, TEXT("Wokrkinge"))
		FActorSpawnParameters BlackSpawnParams;
		BlackSpawnParams.Owner = this;
		BlackSpawnParams.Instigator = Instigator;
		GetWorld()->SpawnActor<AFPSBlackHole>(BlackClass, FVector(0.f, 0.f, 1000.f), FRotator::ZeroRotator, BlackSpawnParams);
	}
	else if (CodeSequence == "URBOTS")
	{
		UE_LOG(LogTemp, Warning, TEXT("Wokrkinge"))
		FActorSpawnParameters BlackSpawnParams;
		BlackSpawnParams.Owner = this;
		BlackSpawnParams.Instigator = Instigator;
		GetWorld()->SpawnActor<AFPSBlackHole>(BlackClass, FVector(0.f, 0.f, 1000.f), FRotator::ZeroRotator, BlackSpawnParams);;// Just another example to show that you can handle more than one match possibility
	}
	// etc.
}
