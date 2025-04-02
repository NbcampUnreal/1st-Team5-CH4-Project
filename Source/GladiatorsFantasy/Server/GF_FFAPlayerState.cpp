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
