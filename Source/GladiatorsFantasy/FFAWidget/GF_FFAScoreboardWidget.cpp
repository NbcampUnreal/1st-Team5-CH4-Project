#include "FFAWidget/GF_FFAScoreboardWidget.h"
#include "Components/TextBlock.h"

void UGF_FFAScoreboardWidget::UpdateTimer(int32 TimerRemainingSeconds)
{
	const int32 Minutes = TimerRemainingSeconds / 60;
	const int32 Seconds = TimerRemainingSeconds % 60;
	const FString TimeString = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);

	if (TimerText)
	{
		TimerText->SetText(FText::FromString(TimeString));
	}
}

void UGF_FFAScoreboardWidget::UpdateKillCount(int32 KillCount)
{
	if (KillCountText)
	{
		const FString KillString = FString::Printf(TEXT("Kills: %d"), KillCount);
		KillCountText->SetText(FText::FromString(KillString));
	}
}
