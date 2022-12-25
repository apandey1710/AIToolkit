// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AITUtilities.generated.h"

/**
 * 
 */
UCLASS()
class AITOOLKIT_API UAITUtilities : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	static void PrintDebugMessage(float TimeToDisplay, FColor Color, const FString& message);

};
