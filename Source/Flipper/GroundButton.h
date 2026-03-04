#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GroundButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonStateChangedSignature, AGroundButton*, ToggledButton);

UCLASS()
class FLIPPER_API AGroundButton : public AActor
{
	GENERATED_BODY()

public:
	AGroundButton();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* ButtonMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USphereComponent* TriggerSphere;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blinking Settings")
	float BlinkingTime = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blinking Settings")
	int BlinkCount = 3;
	
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnButtonStateChangedSignature OnButtonStateChanged;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UScoreComponent* ScoreComponent;
	
	UFUNCTION()
	void ResetButton();
	
	UFUNCTION()
	bool IsLit() const { return bIsLit; };

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	void StartBlinking();
	void Blink();
	
	bool bIsBlinking;
	bool bIsLit;
	int BlinkCounter;
	
	FTimerHandle BlinkTimerHandle;
	
	UPROPERTY()
	class UMaterialInstanceDynamic* DynamicMaterial;
};