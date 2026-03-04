// Fill out your copyright notice in the Description page of Project Settings.


#include "NeonWaveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values for this component's properties
UNeonWaveComponent::UNeonWaveComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false; 

	bIsWaveActive = false;
	CurrentWaveRadius = 0.0f;
	LastHitTime = -9999.0f;
}

void UNeonWaveComponent::BeginPlay()
{
	Super::BeginPlay();
	MeshComponent = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
	if (MeshComponent)
	{
		DynamicMaterial = MeshComponent->CreateAndSetMaterialInstanceDynamic(0);
		MeshComponent->SetNotifyRigidBodyCollision(true);
		MeshComponent->OnComponentHit.AddDynamic(this, &UNeonWaveComponent::OnWallHit);
		if (DynamicMaterial)
		{
			DynamicMaterial->SetScalarParameterValue(FName("WaveThickness"), WaveThickness);
		}
	}
}

void UNeonWaveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsWaveActive && DynamicMaterial)
	{
		CurrentWaveRadius += WaveExpansionSpeed * DeltaTime;
		
		DynamicMaterial->SetScalarParameterValue(FName("WaveRadius"), CurrentWaveRadius);
		
		if (CurrentWaveRadius >= MaxWaveRadius)
		{
			bIsWaveActive = false;
			CurrentWaveRadius = 0.0f;
			DynamicMaterial->SetScalarParameterValue(FName("WaveRadius"), 0.0f);
			SetComponentTickEnabled(false); 
		}
	}
}

void UNeonWaveComponent::OnWallHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	float CurrentTime = GetWorld()->GetTimeSeconds();
	if (CurrentTime - LastHitTime < WaveCooldown)
	{
		return; 
	}
	LastHitTime = CurrentTime;
	
	if (DynamicMaterial)
	{
		DynamicMaterial->SetVectorParameterValue(FName("HitLocation"), Hit.ImpactPoint);
		
		CurrentWaveRadius = 0.0f;
		bIsWaveActive = true;
		
		SetComponentTickEnabled(true); 
	}
}

