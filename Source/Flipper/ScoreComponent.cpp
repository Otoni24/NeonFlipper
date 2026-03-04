#include "ScoreComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FlipperGameMode.h"
#include "FloatingScore.h"

UScoreComponent::UScoreComponent()
{
	PrimaryComponentTick.bCanEverTick = false; 
}

void UScoreComponent::TriggerScore()
{
	AFlipperGameMode* GameMode = Cast<AFlipperGameMode>(UGameplayStatics::GetGameMode(this));
	if (GameMode)
	{
		GameMode->AddScore(ScoreAmount);
	}
	
	if (FloatingTextClass)
	{
		AActor* Owner = GetOwner();
		if (Owner)
		{
			FVector SpawnLocation = Owner->GetActorLocation();
			SpawnLocation.Z += 200.0f;
			
			AFloatingScore* SpawnedText = GetWorld()->SpawnActor<AFloatingScore>(FloatingTextClass, SpawnLocation, FRotator::ZeroRotator);
			
			if (SpawnedText)
			{
				SpawnedText->InitializeScore(ScoreAmount, TextColor);
			}
		}
	}
}