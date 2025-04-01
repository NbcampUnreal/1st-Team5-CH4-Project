#include "Server/GF_FFAGameState.h"
#include "Net/UnrealNetwork.h"

AGF_FFAGameState::AGF_FFAGameState()
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = false;
}

void AGF_FFAGameState::StartCountdown(int32 Duration)
{
	TimeRemaining = Duration;

	GetWorldTimerManager().SetTimer(
		CountdownTimerHandle,
		this,
		&AGF_FFAGameState::TickCountdown,
		1.0f,
		true
	);
}

int32 AGF_FFAGameState::GetTimerRemaining() const
{
	return TimeRemaining;
}

void AGF_FFAGameState::OnRep_TimeRemaining()
{
	// UI 변경 로직
}

void AGF_FFAGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGF_FFAGameState, TimeRemaining);
}

void AGF_FFAGameState::TickCountdown()
{
	TimeRemaining--;

	if (TimeRemaining <= 0)
	{
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
		// 게임 종료 처리 로직
	}
}
