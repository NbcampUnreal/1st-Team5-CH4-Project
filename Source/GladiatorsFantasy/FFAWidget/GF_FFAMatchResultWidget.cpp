#include "FFAWidget/GF_FFAMatchResultWidget.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerState.h"

void UGF_FFAMatchResultWidget::ShowMatchResult(APlayerState* Winner)
{
	if (!MatchResultText) return;

	if (Winner)
	{
		FString WinnerName = Winner->GetPlayerName();
		FString ResultText = FString::Printf(TEXT("%s WIN!"), *WinnerName);
		MatchResultText->SetText(FText::FromString(ResultText));
	}
	else
	{
		MatchResultText->SetText(FText::FromString(TEXT("Draw!")));
	}
}
