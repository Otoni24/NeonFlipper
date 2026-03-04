// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NeonWaveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class FLIPPER_API UNeonWaveComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UNeonWaveComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION()
	void OnWallHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UPROPERTY(EditAnywhere, Category = "Neon Wave")
	float MaxWaveRadius = 300.0f;

	UPROPERTY(EditAnywhere, Category = "Neon Wave")
	float WaveExpansionSpeed = 800.0f;
	
	UPROPERTY(EditAnywhere, Category = "Neon Wave")
	float WaveThickness = 15.f;
	
	UPROPERTY(EditAnywhere, Category = "Wave Settings")
	float WaveCooldown = 0.5f;
private:
	UPROPERTY()
	class UMaterialInstanceDynamic* DynamicMaterial;
	
	UPROPERTY()
	class UStaticMeshComponent* MeshComponent;
	
	bool bIsWaveActive;
	float CurrentWaveRadius;
	float LastHitTime;
};
