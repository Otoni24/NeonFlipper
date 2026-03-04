#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ButtonBank.generated.h"

UCLASS()
class FLIPPER_API AButtonBank : public AActor
{
	GENERATED_BODY()
    
public:    
	AButtonBank();

protected:
	virtual void BeginPlay() override;

public:    
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* BankMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UScoreComponent* ScoreComponent;

private:
	UFUNCTION()
	void OnBankHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	void CheckAndResetButtons();
	
	void SetButtonLight(int32 ButtonIndex, bool bTurnOn);
	
	void ExecuteReset();
	
	bool bIsButton0Lit;
	bool bIsButton1Lit;
	bool bIsButton2Lit;
	
	UPROPERTY()
	class UMaterialInstanceDynamic* DynMatButton1;
    
	UPROPERTY()
	class UMaterialInstanceDynamic* DynMatButton2;
    
	UPROPERTY()
	class UMaterialInstanceDynamic* DynMatButton3;
	
	float LastHitTime;
	bool bIsResetting;
	FTimerHandle ResetTimerHandle;
};