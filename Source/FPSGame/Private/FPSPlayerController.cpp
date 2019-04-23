// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSPlayerController.h"
#include "FPSBlackHole.h"
#include "Engine/World.h"

bool AFPSPlayerController::InputKey(FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad)
{
	Super::InputKey(Key, EventType, AmountDepressed, bGamepad);

	     // Only bother with presses (not releases) and don't worry about mouse button events
     if (InputType == EInputEvent::IE_Pressed && Key.IsMouseButton() == false)
     {
         // Clear the CodeSequence string if the last key press was more than 2 seconds ago
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

	bool bSequenceExpired = TimeSinceLastKeyPress > 2.0f;  // arbitrarily choosing 2 seconds for this example
	if (bSequenceExpired)
	{
		// If more than 2 seconds has passed since the last key press, reset the string; otherwise, don't do anything
		CodeSequence = "";    // reset the string back to a blank, empty string
	}
}


void AFPSPlayerController::CheckCodeSequence()
{
	if (CodeSequence == "EZGAME")
	{
		// Do something to handle this match, e.g. spawn your actor(s)
	}
	else if (CodeSequence == "EXAMPLE2")
	{
		// Just another example to show that you can handle more than one match possibility
	}
	// etc.
}
