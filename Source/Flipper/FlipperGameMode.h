#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FlipperGameMode.generated.h"

UCLASS()
class FLIPPER_API AFlipperGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
public:
	AFlipperGameMode();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pinball Settings")
	TSubclassOf<class AActor> BallClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pinball Settings")
	FVector BallSpawnLocation;
	
	UFUNCTION(BlueprintCallable, Category = "Pinball Logic")
	void RespawnBall();
	
	//Life System
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pinball Settings|Lives")
	int32 MaxLives = 3;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pinball Settings|Lives")
	int32 CurrentLives;
	
	UFUNCTION(BlueprintCallable, Category = "Pinball Logic")
	void LoseLife();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Pinball Logic|UI")
	void OnLivesUpdated(int32 NewLivesCount);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Pinball Logic")
	void OnGameOver();
	
	//Score System
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pinball Settings|Score")
	int32 CurrentScore = 0;
	
	UFUNCTION(BlueprintCallable, Category = "Pinball Logic")
	void AddScore(int32 PointsToAdd);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Pinball Logic|UI")
	void OnScoreUpdated(int32 NewScore);
};