// Fill out your copyright notice in the Description page of Project Settings.


#include "Racket.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Engine/Engine.h"

// Sets default values
ARacket::ARacket()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;
	
	RacketMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RacketMesh"));
	RacketMesh->SetupAttachment(RootComponent);
	RacketMesh->SetNotifyRigidBodyCollision(true);
	
	Hinge = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Hinge"));
	Hinge->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ARacket::BeginPlay()
{
	Super::BeginPlay();
	InitialRotation = GetActorRotation();
	if (RacketMesh)
	{
		DynamicMaterial = RacketMesh->CreateAndSetMaterialInstanceDynamic(0);
		RacketMesh->OnComponentHit.AddDynamic(this, &ARacket::OnRacketHit);
	}
	if (Hinge)
	{
		if (ActorHasTag(FName("Left")))
		{
			Hinge->SetAngularOrientationTarget(FRotator(0.f, 30.f, 0.f));
		}
		if (ActorHasTag(FName("Right")))
		{
			Hinge->SetAngularOrientationTarget(FRotator(0.f, -30.f, 0.f));
		}
	}
}

void ARacket::OnRacketHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this && OtherComp->IsSimulatingPhysics())
	{
		bIsFlashing = true;
		FlashTimer = 0.0f;
		SetActorTickEnabled(true);
	}
}

void ARacket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bIsFlashing && DynamicMaterial)
	{
		FlashTimer += DeltaTime;
		float Alpha = FlashTimer / FlashDuration;
		
		DynamicMaterial->SetScalarParameterValue(FName("BumperFlash"), 1.0f);

		if (FlashTimer >= FlashDuration)
		{
			bIsFlashing = false;
			DynamicMaterial->SetScalarParameterValue(FName("BumperFlash"), 0.0f);
			SetActorTickEnabled(false);
		}
	}
}

void ARacket::PressRacket()
{
	if (RacketMesh)
	{
		RacketMesh->WakeRigidBody();
		if (Hinge)
		{
			if (ActorHasTag(FName("Left")))
			{
				Hinge->SetAngularOrientationTarget(FRotator(0.f, -30.f, 0.f));
			}
			if (ActorHasTag(FName("Right")))
			{
				Hinge->SetAngularOrientationTarget(FRotator(0.f, 30.f, 0.f));
			}
		}
	}
}

void ARacket::ReleaseRacket()
{
	if (RacketMesh)
	{
		RacketMesh->WakeRigidBody();
		if (Hinge)
		{
			if (ActorHasTag(FName("Left")))
			{
				Hinge->SetAngularOrientationTarget(FRotator(0.f, 30.f, 0.f));
			}
			if (ActorHasTag(FName("Right")))
			{
				Hinge->SetAngularOrientationTarget(FRotator(0.f, -30.f, 0.f));
			}
		}
	}

}

