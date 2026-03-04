// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bumper.generated.h"

UCLASS()
class FLIPPER_API ABumper : public AActor
{
	GENERATED_BODY()

public:
	ABumper();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* BumperMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bumper Settings")
	float BounceForce = 2000.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bumper Settings")
	float FlashDuration = 0.1f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UScoreComponent* ScoreComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bumper Settings")
	float HitCooldown = 0.05f;
	
	UFUNCTION()
	void OnBumperHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
protected:
	float LastHitTime;
private:
	UPROPERTY()
	class UMaterialInstanceDynamic* DynamicMaterial;
	
	bool bIsFlashing;
	float FlashTimer;
};
