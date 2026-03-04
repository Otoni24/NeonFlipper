// Fill out your copyright notice in the Description page of Project Settings.


#include "GroundButton.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "ScoreComponent.h"


// Sets default values
AGroundButton::AGroundButton()
{
	PrimaryActorTick.bCanEverTick = false;
	
	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LauncherMesh"));
	RootComponent = ButtonMesh;
	
	TriggerSphere = CreateDefaultSubobject<USphereComponent>(TEXT("TriggerBox"));
	TriggerSphere->SetupAttachment(RootComponent);
	
	bIsBlinking = false;
	bIsLit = false;
	
	ScoreComponent = CreateDefaultSubobject<UScoreComponent>(TEXT("ScoreComponent"));
}

void AGroundButton::BeginPlay()
{
	Super::BeginPlay();
	if (TriggerSphere)
	{
		TriggerSphere->OnComponentBeginOverlap.AddDynamic(this, &AGroundButton::OnOverlapBegin);
	}
	if (ButtonMesh)
	{
		DynamicMaterial = ButtonMesh->CreateAndSetMaterialInstanceDynamic(0);
	}
}

void AGroundButton::ResetButton()
{
	if (ScoreComponent)
	{
		ScoreComponent->TriggerScore();
	}
	StartBlinking();	
}

void AGroundButton::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bIsBlinking) return;
	if (OtherComp && OtherComp->IsSimulatingPhysics())
	{
		float ButtonState = 1.f;
		bIsLit = true;
		DynamicMaterial->SetScalarParameterValue(FName("ButtonState"), ButtonState);
		
		OnButtonStateChanged.Broadcast(this);
	}
}

void AGroundButton::StartBlinking()
{
	bIsBlinking = true;
	BlinkCounter = 0;
	bIsLit = false;
	GetWorld()->GetTimerManager().SetTimer(BlinkTimerHandle, this, &AGroundButton::Blink, 0.2f, true);
}

void AGroundButton::Blink()
{
	bIsLit = !bIsLit;
	
	float EmissionValue = bIsLit ? 1.0f : 0.0f;
	if (DynamicMaterial)
	{
		DynamicMaterial->SetScalarParameterValue(FName("ButtonState"), EmissionValue);
	}
	
	BlinkCounter++;
	
	if (BlinkCounter >= BlinkCount*2)
	{
		GetWorld()->GetTimerManager().ClearTimer(BlinkTimerHandle);
		
		bIsLit = false;
		bIsBlinking = false;
		DynamicMaterial->SetScalarParameterValue(FName("ButtonState"), 0.0f);
	}
}

void AGroundButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

