// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GFBaseCharacter.h"
#include "GFMagician.generated.h"

UCLASS()
class GLADIATORSFANTASY_API AGFMagician : public AGFBaseCharacter
{
	GENERATED_BODY()

public:

	AGFMagician();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
