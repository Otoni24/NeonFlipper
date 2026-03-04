#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GroundButtonManager.generated.h"

UCLASS()
class FLIPPER_API AGroundButtonManager : public AActor
{
	GENERATED_BODY()

public:

	AGroundButtonManager();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category = "Buttons Setup")
	TArray<AGroundButton*> LinkedButtons;
	
private:
	UFUNCTION()
	void HandleButtonToggled(AGroundButton* ButtonThatToggled);
};
