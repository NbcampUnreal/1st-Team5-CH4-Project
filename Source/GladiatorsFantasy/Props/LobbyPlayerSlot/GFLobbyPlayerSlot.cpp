#include "Props/LobbyPlayerSlot/GFLobbyPlayerSlot.h"
#include "Character/MainLoby/GFMainLobyPlayerController.h"


AGFLobbyPlayerSlot::AGFLobbyPlayerSlot()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	bNetLoadOnClient = true;

	StaticMeshCompo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMeshCompo;
}

void AGFLobbyPlayerSlot::BeginPlay()
{
	Super::BeginPlay();

	if (!SelectedCharacter)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SelectedCharacter =  GetWorld()->SpawnActor<AGFLobbySelectedCharacter>(GetActorLocation(), GetActorRotation(), SpawnParams);
	}
	
	if (ReplicatedMesh)
	{
		SelectedCharacter->SkeletalMeshCompo->SetSkeletalMesh(ReplicatedMesh);
	}
	
	if (ReplicatedAnim)
	{
		SelectedCharacter->SkeletalMeshCompo->SetAnimation(ReplicatedAnim);
		SelectedCharacter->SkeletalMeshCompo->PlayAnimation(ReplicatedAnim, true);
	}
}

void AGFLobbyPlayerSlot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGFLobbyPlayerSlot::OnRep_CharacterMesh()
{
	if (SelectedCharacter && ReplicatedMesh)
	{
		SelectedCharacter->SkeletalMeshCompo->SetSkeletalMesh(ReplicatedMesh);
	}
}

void AGFLobbyPlayerSlot::OnRep_AnimSecquence()
{
	if (SelectedCharacter && ReplicatedAnim)
	{
		SelectedCharacter->SkeletalMeshCompo->SetAnimation(ReplicatedAnim);
		SelectedCharacter->SkeletalMeshCompo->PlayAnimation(ReplicatedAnim, true);
	}
}

void AGFLobbyPlayerSlot::AddSelectedActor(APlayerController* In_PlayerController)
{
	PlayerController = In_PlayerController;
	if (PlayerController)
	{
		AGFMainLobyPlayerController* MainLobbyController = Cast<AGFMainLobyPlayerController>(PlayerController);
		if (MainLobbyController)
		{
			MainLobbyController->SetSlot(this);
		}
	}

	if (SelectedCharacter)
	{
		SelectedCharacter->Destroy();
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SelectedCharacter =  GetWorld()->SpawnActor<AGFLobbySelectedCharacter>(GetActorLocation(), GetActorRotation(), SpawnParams);
}

void AGFLobbyPlayerSlot::RemoveSelectedActor()
{
	PlayerController = nullptr;

	if (SelectedCharacter)
	{
		SelectedCharacter->Destroy();
		SelectedCharacter = nullptr;
	}
}

void AGFLobbyPlayerSlot::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AGFLobbyPlayerSlot, SelectedCharacter);
	DOREPLIFETIME(AGFLobbyPlayerSlot, ReplicatedMesh);
	DOREPLIFETIME(AGFLobbyPlayerSlot, ReplicatedAnim);
	DOREPLIFETIME(AGFLobbyPlayerSlot, SlotNumber);
	DOREPLIFETIME(AGFLobbyPlayerSlot, AnimType);
}