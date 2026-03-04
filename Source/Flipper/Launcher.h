#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Launcher.generated.h"

UCLASS()
class FLIPPER_API ALauncher : public AActor
{
	GENERATED_BODY()

public:
	ALauncher();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* LauncherMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* TriggerBox;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UArrowComponent* LaunchDirectionIndicator;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Launcher Settings")
	float LaunchDelay = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Launcher Settings")
	float MinLaunchForce = 2600.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Launcher Settings")
	float MaxLaunchForce = 3400.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bumper Settings")
	float FlashDuration = 0.1f;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void ExecuteLaunch();

	FTimerHandle LaunchTimerHandle;
	bool bIsFlashing;
	float FlashTimer;
	
	UPROPERTY()
	class UPrimitiveComponent* BallComponent;
	
	UPROPERTY()
	class UMaterialInstanceDynamic* DynamicMaterial;
};