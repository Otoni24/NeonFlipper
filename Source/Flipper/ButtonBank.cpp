#include "ButtonBank.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"
#include "ScoreComponent.h"

AButtonBank::AButtonBank()
{
    PrimaryActorTick.bCanEverTick = false;

    BankMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BankMesh"));
    RootComponent = BankMesh;
    
    BankMesh->SetNotifyRigidBodyCollision(true);
    
    LastHitTime = 0.0f;
    bIsResetting = false;
    
    ScoreComponent = CreateDefaultSubobject<UScoreComponent>(TEXT("ScoreComponent"));
}

void AButtonBank::BeginPlay()
{
    Super::BeginPlay();
    
    if (BankMesh)
    {
        DynMatButton1 = BankMesh->CreateAndSetMaterialInstanceDynamic(0);
        DynMatButton2 = BankMesh->CreateAndSetMaterialInstanceDynamic(1);
        DynMatButton3 = BankMesh->CreateAndSetMaterialInstanceDynamic(2);

        BankMesh->OnComponentHit.AddDynamic(this, &AButtonBank::OnBankHit);
    }
}

void AButtonBank::OnBankHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (bIsResetting) return; 
    
    float CurrentTime = GetWorld()->GetTimeSeconds();
    if (CurrentTime - LastHitTime < 0.2f) return;
    
    if (OtherActor && OtherActor != this)
    {
        FVector TraceStart = Hit.ImpactPoint - (Hit.ImpactNormal * 20.0f);
        FVector TraceEnd = Hit.ImpactPoint + (Hit.ImpactNormal * 20.0f);

        FCollisionQueryParams QueryParams;
        QueryParams.bReturnFaceIndex = true;
        QueryParams.bTraceComplex = true;

        FHitResult TraceHit;
        
        bool bHit = BankMesh->LineTraceComponent(TraceHit, TraceStart, TraceEnd, QueryParams);

        if (GetWorld())
        {
            DrawDebugLine(GetWorld(), TraceStart, TraceEnd, bHit ? FColor::Green : FColor::Red, false, 2.0f, 0, 1.0f);
        }

        if (bHit)
        {
            if (TraceHit.FaceIndex != -1)
            {
                int32 SectionIndex = -1;
                BankMesh->GetMaterialFromCollisionFaceIndex(TraceHit.FaceIndex, SectionIndex);
                
                bool bValidButtonHit = false;
                
                switch (SectionIndex)
                {
                case 0:
                    bValidButtonHit = true;
                    if (!bIsButton0Lit)
                    {
                        bIsButton0Lit = true;
                        SetButtonLight(0, true);
                        CheckAndResetButtons();
                    } else
                    {
                        bIsButton0Lit = false;
                        SetButtonLight(0, false);
                    }
                    break;
                case 1:
                    bValidButtonHit = true;
                    if (!bIsButton1Lit)
                    {
                        bIsButton1Lit = true;
                        SetButtonLight(1, true);
                        CheckAndResetButtons();
                    } else
                    {
                        bIsButton1Lit = false;
                        SetButtonLight(1, false);
                    }
                    break;
                case 2:
                    bValidButtonHit = true;
                    if (!bIsButton2Lit)
                    {
                        bIsButton2Lit = true;
                        SetButtonLight(2, true);
                        CheckAndResetButtons();
                    } else
                    {
                        bIsButton2Lit = false;
                        SetButtonLight(2, false);
                    }
                    break;
                default:
                    break; 
                }
                
                if (bValidButtonHit)
                {
                    LastHitTime = CurrentTime;
                }
            }
        }
    }
}

void AButtonBank::SetButtonLight(int32 ButtonIndex, bool bTurnOn)
{
    float ButtonState = bTurnOn ? 1.0f : 0.0f; // 1 acceso, 0 spento

    if (ButtonIndex == 0 && DynMatButton1)
        DynMatButton1->SetScalarParameterValue(FName("ButtonState"), ButtonState);
    else if (ButtonIndex == 1 && DynMatButton2)
        DynMatButton2->SetScalarParameterValue(FName("ButtonState"), ButtonState);
    else if (ButtonIndex == 2 && DynMatButton3)
        DynMatButton3->SetScalarParameterValue(FName("ButtonState"), ButtonState);
}

void AButtonBank::ExecuteReset()
{
    bIsButton0Lit = false;
    bIsButton1Lit = false;
    bIsButton2Lit = false;

    SetButtonLight(0, false);
    SetButtonLight(1, false);
    SetButtonLight(2, false);
    
    bIsResetting = false;
}

void AButtonBank::CheckAndResetButtons()
{
    if (bIsButton0Lit && bIsButton1Lit && bIsButton2Lit)
    {
        bIsResetting = true;
        if (ScoreComponent)
        {
            ScoreComponent->TriggerScore();
        }
        GetWorld()->GetTimerManager().SetTimer(ResetTimerHandle, this, &AButtonBank::ExecuteReset, 0.4f, false);
    }
}
