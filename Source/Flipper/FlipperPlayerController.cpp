#include "FlipperPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Racket.h"
#include "Kismet/GameplayStatics.h"

void AFlipperPlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        Subsystem->AddMappingContext(FlipperMappingContext, 0);
    }
    
    TArray<AActor*> FoundRackets;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARacket::StaticClass(), FoundRackets);

    for (AActor* Actor : FoundRackets)
    {
        if (Actor->ActorHasTag(FName("Left"))) LeftRacket = Cast<ARacket>(Actor);
        if (Actor->ActorHasTag(FName("Right"))) RightRacket = Cast<ARacket>(Actor);
    }
}

void AFlipperPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
    {
        EnhancedInputComponent->BindAction(ActionLeftRacket, ETriggerEvent::Started, this, &AFlipperPlayerController::HandleLeftPress);
        EnhancedInputComponent->BindAction(ActionLeftRacket, ETriggerEvent::Completed, this, &AFlipperPlayerController::HandleLeftRelease);
        
        EnhancedInputComponent->BindAction(ActionRightRacket, ETriggerEvent::Started, this, &AFlipperPlayerController::HandleRightPress);
        EnhancedInputComponent->BindAction(ActionRightRacket, ETriggerEvent::Completed, this, &AFlipperPlayerController::HandleRightRelease);
        
        EnhancedInputComponent->BindAction(ActionPause, ETriggerEvent::Started, this, &AFlipperPlayerController::TogglePause);
    }
}

void AFlipperPlayerController::TogglePause()
{
    bool bIsPaused = UGameplayStatics::IsGamePaused(this);
    bool bNewPauseState = !bIsPaused;
    
    UGameplayStatics::SetGamePaused(this, !bIsPaused);

    if (!bIsPaused) 
    {
        bShowMouseCursor = true;
        
        FInputModeGameAndUI InputMode;
        SetInputMode(InputMode);
    }
    else 
    {
        bShowMouseCursor = false;
        
        FInputModeGameOnly InputMode;
        SetInputMode(InputMode);
    }
    OnTogglePauseUI(bNewPauseState);
}

void AFlipperPlayerController::HandleLeftPress()
{
    UE_LOG(LogTemp, Warning, TEXT("INPUT RILEVATO: Sinistro!")); 
    if(LeftRacket) 
    {
        LeftRacket->PressRacket(); 
    }
    else 
    {
        UE_LOG(LogTemp, Error, TEXT("ERRORE: LeftRacket è NULL!"));
    }
}
void AFlipperPlayerController::HandleLeftRelease() { if(LeftRacket) LeftRacket->ReleaseRacket(); }
void AFlipperPlayerController::HandleRightPress() { if(RightRacket) RightRacket->PressRacket(); }
void AFlipperPlayerController::HandleRightRelease() { if(RightRacket) RightRacket->ReleaseRacket(); }