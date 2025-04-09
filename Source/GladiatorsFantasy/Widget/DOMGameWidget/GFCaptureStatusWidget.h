#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GFCaptureStatusWidget.generated.h"

UCLASS()
class GLADIATORSFANTASY_API UGFCaptureStatusWidget : public UUserWidget
{
	GENERATED_BODY()

	
public:
    // 점령 게이지를 0~100 기준으로 업데이트
    UFUNCTION(BlueprintCallable)
    void UpdateGauge(float CaptureGauge, FName CapturingTeam);

protected:
    // 위젯에서 연결할 ProgressBar/Texts
    UPROPERTY(meta = (BindWidget))
    class UProgressBar* TeamAProgressBar;

    UPROPERTY(meta = (BindWidget))
    class UProgressBar* TeamBProgressBar;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* TeamAPercentText;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* TeamBPercentText;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* CapturePointLabel;
};
