// Fill out your copyright notice in the Description page of Project Settings.


#include "GroundButtonManager.h"

#include "GroundButton.h"


// Sets default values
AGroundButtonManager::AGroundButtonManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AGroundButtonManager::BeginPlay()
{
	Super::BeginPlay();
	
	for (AGroundButton* MyButton : LinkedButtons)
	{
		if (MyButton)
		{
			MyButton->OnButtonStateChanged.AddDynamic(this, &AGroundButtonManager::HandleButtonToggled);
		}
	}
}

void AGroundButtonManager::HandleButtonToggled(AGroundButton* ButtonThatToggled)
{
	bool bAllButtonsLit = true;

	for (AGroundButton* GroundButton : LinkedButtons)
	{
		if (GroundButton && !GroundButton->IsLit()) bAllButtonsLit = false;
	}
	if (bAllButtonsLit)
	{
		for (AGroundButton* GroundButton : LinkedButtons)
		{
			if (GroundButton)
			{
				GroundButton->ResetButton();
			}
		}

	} 
}