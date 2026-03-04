#include "DeathZone.h"
#include "Components/BoxComponent.h"
#include "FlipperGameMode.h"
#include "Kismet/GameplayStatics.h"

ADeathZone::ADeathZone()
{
	PrimaryActorTick.bCanEverTick = false;
    
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;
}

void ADeathZone::BeginPlay()
{
	Super::BeginPlay();
	
	if (TriggerBox)
	{
		TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ADeathZone::OnOverlapBegin);
	}
}

void ADeathZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp && OtherComp->IsSimulatingPhysics())
	{
		OtherActor->Destroy();
	}
	AFlipperGameMode* MyGameMode = Cast<AFlipperGameMode>(UGameplayStatics::GetGameMode(this));
	
	if (MyGameMode)
	{
		MyGameMode->LoseLife();
	}
}

