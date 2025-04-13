#include "Props/LobbySelectedCharacter/GFLobbySelectedCharacter.h"

#include "Net/UnrealNetwork.h"

AGFLobbySelectedCharacter::AGFLobbySelectedCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	SetReplicateMovement(true);

	SkeletalMeshCompo = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	RootComponent = SkeletalMeshCompo;
}

void AGFLobbySelectedCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGFLobbySelectedCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("[%s] 서버에서 스폰: %s"), HasAuthority() ? TEXT("SERVER") : TEXT("CLIENT"), *GetName());
}

void AGFLobbySelectedCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}