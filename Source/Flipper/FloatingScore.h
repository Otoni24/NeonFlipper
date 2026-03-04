#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingScore.generated.h"

UCLASS()
class FLIPPER_API AFloatingScore : public AActor
{
	GENERATED_BODY()
	
public:	
	UFUNCTION(BlueprintImplementableEvent, Category = "Scoring")
	void InitializeScore(int32 ScoreValue, FLinearColor TextColor);
};