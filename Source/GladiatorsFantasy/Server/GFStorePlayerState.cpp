#include "Server/GFStorePlayerState.h"
#include "Net/UnrealNetwork.h"

void AGFStorePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AGFStorePlayerState, bIsReady);
}