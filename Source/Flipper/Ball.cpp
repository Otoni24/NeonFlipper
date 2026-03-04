#include "Ball.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"

ABall::ABall()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	RootComponent = CollisionSphere;
	CollisionSphere->InitSphereRadius(50.0f);
	
	CollisionSphere->SetSimulatePhysics(true);
	CollisionSphere->SetNotifyRigidBodyCollision(true);
	CollisionSphere->SetCollisionProfileName(TEXT("PhysicsActor"));
	CollisionSphere->SetEnableGravity(false);
	CollisionSphere->BodyInstance.bUseCCD = true;
	
	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
	BallMesh->SetupAttachment(RootComponent);
	BallMesh->SetCollisionProfileName(TEXT("NoCollision"));
	
	TrailComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("TrailComponent"));
	TrailComponent->SetupAttachment(RootComponent);
	
	TrailComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -TrailRadius));
}

void ABall::BeginPlay()
{
	Super::BeginPlay();
	
	if (CollisionSphere)
	{
		CollisionSphere->OnComponentHit.AddDynamic(this, &ABall::OnHit);
	}
	
	if (BallMesh)
	{
		DynamicMaterial = BallMesh->CreateAndSetMaterialInstanceDynamic(0);
		DynamicMaterial2 = BallMesh->CreateAndSetMaterialInstanceDynamic(1);
	}
}

void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector CustomGravity = FVector(0.0f, 2000.0f, -2200.0f);
	
	CollisionSphere->AddForce(CustomGravity, NAME_None, true);
	
	DynamicMaterial->SetVectorParameterValue(FName("BallVelocity"), GetVelocity());
	DynamicMaterial2->SetVectorParameterValue(FName("BallVelocity"), GetVelocity());
}

void ABall::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
}
