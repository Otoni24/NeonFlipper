#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScoreComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FLIPPER_API UScoreComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UScoreComponent();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoring")
	int32 ScoreAmount = 100;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoring")
	FLinearColor TextColor = FLinearColor::Yellow;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Scoring")
	TSubclassOf<class AFloatingScore> FloatingTextClass;
	
	UFUNCTION(BlueprintCallable, Category = "Scoring")
	void TriggerScore();
};