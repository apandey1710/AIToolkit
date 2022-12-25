// Fill out your copyright notice in the Description page of Project Settings.


#include "AITUtilities.h"


void UAITUtilities::PrintDebugMessage(float TimeToDisplay, FColor Color, const FString&  message)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, message);	
	}
}


