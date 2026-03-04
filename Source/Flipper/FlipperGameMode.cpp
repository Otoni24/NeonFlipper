#include "FlipperGameMode.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

void AFlipperGameMode::BeginPlay()
{
	Super::BeginPlay();
	CurrentLives = MaxLives;
	RespawnBall();
}

AFlipperGameMode::AFlipperGameMode()
{
	BallSpawnLocation = FVector(0.0f, 0.0f, 100.0f);
}

void AFlipperGameMode::RespawnBall()
{
	if (GetWorld() && BallClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AActor* NewBall = GetWorld()->SpawnActor<AActor>(BallClass, BallSpawnLocation, FRotator::ZeroRotator, SpawnParams);
	}
}

void AFlipperGameMode::LoseLife()
{
	CurrentLives--;
	OnLivesUpdated(CurrentLives);
	if (CurrentLives >= 0)
	{
		RespawnBall();
	}
	else
	{
		OnGameOver();
	}
}

void AFlipperGameMode::AddScore(int32 PointsToAdd)
{
	CurrentScore += PointsToAdd;
	
	OnScoreUpdated(CurrentScore);
}
