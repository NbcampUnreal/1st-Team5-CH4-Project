#include "Component/MultiplayerEventsManager/GFMultiplayerEventsManager.h"
#include "Net/UnrealNetwork.h"

UGFMultiplayerEventsManager::UGFMultiplayerEventsManager()
{
	PrimaryComponentTick.bCanEverTick = true;

	//SetIsReplicated(true);
	SetIsReplicatedByDefault(true);
}

void UGFMultiplayerEventsManager::BeginPlay()
{
	Super::BeginPlay();

	
}


void UGFMultiplayerEventsManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UGFMultiplayerEventsManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UGFMultiplayerEventsManager, TestCurrentTeamTag);
	DOREPLIFETIME(UGFMultiplayerEventsManager, TestMultiplayerGameplayTagsContainer);
}

