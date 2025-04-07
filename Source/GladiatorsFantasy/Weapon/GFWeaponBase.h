// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GFWeaponBase.generated.h"

UENUM(BlueprintType)
enum class EWeaponRarity : uint8
{
	EWR_Nomal, EWR_Rare, EWR_Epic, EWR_Legend, EWR_Max
};

UCLASS()
class GLADIATORSFANTASY_API AGFWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGFWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
