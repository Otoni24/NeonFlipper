#include "Launcher.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "TimerManager.h"

ALauncher::ALauncher()
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = false;
    
    LauncherMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LauncherMesh"));
    RootComponent = LauncherMesh;
    
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    TriggerBox->SetupAttachment(RootComponent);
    
    LaunchDirectionIndicator = CreateDefaultSubobject<UArrowComponent>(TEXT("LaunchDirection"));
    LaunchDirectionIndicator->SetupAttachment(RootComponent);
    
    bIsFlashing = false;
}

void ALauncher::BeginPlay()
{
    Super::BeginPlay();
    
    if (TriggerBox)
    {
        TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ALauncher::OnOverlapBegin);
        TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ALauncher::OnOverlapEnd);
    }
    if (LauncherMesh)
    {
        DynamicMaterial = LauncherMesh->CreateAndSetMaterialInstanceDynamic(0);
    }
}

void ALauncher::Tick(float DeltaTime)
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

void ALauncher::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherComp && OtherComp->IsSimulatingPhysics())
    {
        BallComponent = OtherComp;
        
        GetWorldTimerManager().SetTimer(LaunchTimerHandle, this, &ALauncher::ExecuteLaunch, LaunchDelay, false);
    }
}

void ALauncher::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherComp == BallComponent)
    {
        GetWorldTimerManager().ClearTimer(LaunchTimerHandle);
        BallComponent = nullptr;
    }
}

void ALauncher::ExecuteLaunch()
{
    if (BallComponent)
    {
        FVector LaunchDir = LaunchDirectionIndicator->GetForwardVector();
        float LaunchForce = FMath::FRandRange(MinLaunchForce, MaxLaunchForce);
        
        BallComponent->AddImpulse(LaunchDir * LaunchForce, NAME_None, true);

        if (DynamicMaterial)
        {
            bIsFlashing = true;
            FlashTimer = 0.0f;
            SetActorTickEnabled(true);
        }
    }
}