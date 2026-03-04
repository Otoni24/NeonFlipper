// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Racket.generated.h"

UCLASS()
class FLIPPER_API ARacket : public AActor
{
	GENERATED_BODY()

public:
	ARacket();

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnRacketHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
public:
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable, Category = "Racket")
	void PressRacket();

	UFUNCTION(BlueprintCallable, Category = "Racket")
	void ReleaseRacket();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* RacketMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPhysicsConstraintComponent* Hinge;
	
private:
	UPROPERTY()
	UMaterialInstanceDynamic* DynamicMaterial;
	
	UPROPERTY(EditAnywhere, Category = "Racket Settings")
	float MaxRotationAngle = 45.0f;

	UPROPERTY(EditAnywhere, Category = "Racket Settings")
	float RotationSpeed = 20.0f;
	
	UPROPERTY(EditAnywhere, Category = "Racket Settings")
	float FlashDuration = 0.2f;
	
	bool bIsFlashing = false;
	float FlashTimer = 0.0f;
	
	bool bIsPressed = false;
	FRotator InitialRotation;
	FRotator TargetRotation;
};
