#include "Widget/DOMGameWidget/GFCaptureStatusWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UGFCaptureStatusWidget::UpdateGauge(float CaptureGauge, FName CapturingTeam)
{
    float TeamBPercent = FMath::Clamp(CaptureGauge / 100.f, 0.f, 1.f);
    float TeamAPercent = 1.0f - TeamBPercent;

    if (TeamAProgressBar)
        TeamAProgressBar->SetPercent(TeamAPercent);

    if (TeamBProgressBar)
        TeamBProgressBar->SetPercent(TeamBPercent);

    if (TeamAPercentText)
        TeamAPercentText->SetText(FText::FromString(FString::Printf(TEXT("%d%%"), FMath::RoundToInt(TeamAPercent * 100))));

    if (TeamBPercentText)
        TeamBPercentText->SetText(FText::FromString(FString::Printf(TEXT("%d%%"), FMath::RoundToInt(TeamBPercent * 100))));

    // === 중앙 텍스트 및 색상 설정 ===
    if (CapturePointLabel)
    {
        FLinearColor Color;
        FText LabelText;

        if (CapturingTeam == "TeamA")
        {
            Color = FLinearColor(0.0f, 0.5f, 1.0f);
            LabelText = FText::FromString("A");
        }
        else if (CapturingTeam == "TeamB")
        {
            Color = FLinearColor(1.0f, 0.1f, 0.1f);
            LabelText = FText::FromString("B");
        }
        else
        {
            Color = FLinearColor(0.7f, 0.7f, 0.7f);
            LabelText = FText::FromString("-");
        }

        CapturePointLabel->SetColorAndOpacity(FSlateColor(Color));
        CapturePointLabel->SetText(LabelText);
    }
}
