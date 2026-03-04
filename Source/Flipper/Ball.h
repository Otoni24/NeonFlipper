#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

UCLASS()
class FLIPPER_API ABall : public AActor
{
	GENERATED_BODY()
	
public:	
	ABall();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USphereComponent* CollisionSphere;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* BallMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Effects")
	class UNiagaraComponent* TrailComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	float TrailRadius;
	
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
private:
	UPROPERTY()
	class UMaterialInstanceDynamic* DynamicMaterial;
	UPROPERTY()
	class UMaterialInstanceDynamic* DynamicMaterial2;
};