#include "Bumper.h"
#include "Components/StaticMeshComponent.h"
#include "ScoreComponent.h"

ABumper::ABumper()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	BumperMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BumperMesh"));
	RootComponent = BumperMesh;
	BumperMesh->SetNotifyRigidBodyCollision(true);
	bIsFlashing = false;
	FlashTimer = 0.0f;
	ScoreComponent = CreateDefaultSubobject<UScoreComponent>(TEXT("ScoreComponent"));
	LastHitTime = -HitCooldown;
}

void ABumper::BeginPlay()
{
	Super::BeginPlay();
	if (BumperMesh)
	{
		DynamicMaterial = BumperMesh->CreateAndSetMaterialInstanceDynamic(0);
		
		BumperMesh->OnComponentHit.AddDynamic(this, &ABumper::OnBumperHit);
	}
}

void ABumper::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bIsFlashing && DynamicMaterial)
	{
		FlashTimer += DeltaTime;
		float Alpha = FlashTimer / FlashDuration; 
		
		float CurrentEffectValue = FMath::Lerp(1.0f, 0.0f, Alpha);
		
		DynamicMaterial->SetScalarParameterValue(FName("BumperPush"), CurrentEffectValue);
		DynamicMaterial->SetScalarParameterValue(FName("BumperFlash"), 1.f);
		
		if (FlashTimer >= FlashDuration)
		{
			bIsFlashing = false;
			DynamicMaterial->SetScalarParameterValue(FName("BumperPush"), 0.0f);
			DynamicMaterial->SetScalarParameterValue(FName("BumperFlash"), 0.0f);

			SetActorTickEnabled(false);
		}
	}
}

void ABumper::OnBumperHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	float CurrentTime = GetWorld()->GetTimeSeconds();
	if (CurrentTime - LastHitTime < HitCooldown)
	{
		return; 
	}
	LastHitTime = CurrentTime;
	if (OtherComp && OtherComp->IsSimulatingPhysics())
	{
		FVector PushDirection = Hit.ImpactNormal;
		PushDirection.Z = 0.0f;
		PushDirection.Normalize();
		
		OtherComp->AddImpulse(PushDirection * BounceForce, NAME_None, true);
		
		if (DynamicMaterial)
		{
			bIsFlashing = true;
			FlashTimer = 0.0f;
			SetActorTickEnabled(true);
		}
		
		if (ScoreComponent)
		{
			ScoreComponent->TriggerScore();
		}
	}
}

