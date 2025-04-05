#include "Server/GF_FFAPlayerState.h"
#include "Net/UnrealNetwork.h"

void AGF_FFAPlayerState::AddKill()
{
	KillCount++;
}

int32 AGF_FFAPlayerState::GetKillCount() const
{
	return KillCount;
}

void AGF_FFAPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGF_FFAPlayerState, KillCount);
}
