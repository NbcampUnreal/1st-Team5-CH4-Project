#include "Server/GF_FFAPlayerState.h"
#include "Net/UnrealNetwork.h"

AGF_FFAPlayerState::AGF_FFAPlayerState()
{
	bReplicates = true;
}

int32 AGF_FFAPlayerState::GetKillCount() const
{
	return KillCount;
}

int32 AGF_FFAPlayerState::GetVictoryPoints() const
{
	return VictoryPoints;
}

void AGF_FFAPlayerState::AddKill()
{
	KillCount++;
}

void AGF_FFAPlayerState::AddVictoryPoint()
{
	VictoryPoints++;
}

void AGF_FFAPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGF_FFAPlayerState, KillCount);
	DOREPLIFETIME(AGF_FFAPlayerState, VictoryPoints);
}
