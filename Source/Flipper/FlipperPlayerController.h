// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "FlipperPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
class ARacket;

UCLASS()
class FLIPPER_API AFlipperPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* ActionPause;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void OnTogglePauseUI(bool bIsPaused);
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
	UFUNCTION(BlueprintCallable, Category = "Pause")
	void TogglePause();
	
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* FlipperMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* ActionLeftRacket;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* ActionRightRacket;

private:
	ARacket* LeftRacket;
	ARacket* RightRacket;
	
	void HandleLeftPress();
	void HandleLeftRelease();
	void HandleRightPress();
	void HandleRightRelease();
};
