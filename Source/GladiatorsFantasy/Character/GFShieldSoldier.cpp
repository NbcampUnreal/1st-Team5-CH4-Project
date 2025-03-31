// Fill out your copyright notice in the Description page of Project Settings.


#include "GFShieldSoldier.h"

// Sets default values
AGFShieldSoldier::AGFShieldSoldier()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGFShieldSoldier::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGFShieldSoldier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGFShieldSoldier::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

