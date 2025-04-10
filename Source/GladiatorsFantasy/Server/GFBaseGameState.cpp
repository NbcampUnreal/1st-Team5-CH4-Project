#include "Server/GFBaseGameState.h"
#include "Net/UnrealNetwork.h"
#include "Character/GFPlayerController.h"
#include "Character/MainLoby/GFMainLobyPlayerController.h"

#include "Widget/DOMGameWidget/GFCaptureStatusWidget.h"

AGFBaseGameState::AGFBaseGameState()
{
}

void AGFBaseGameState::BroadcastMessage_Implementation(const FString& SenderName, const FString& TeamTagName, const FString& Message, EMessage_Type MessageType)
{
	FString FullMessage = FString::Printf(TEXT("[%s]: %s"), *SenderName, *Message);

	APlayerController* LocalController = GetWorld()->GetFirstPlayerController();
	if (LocalController)
	{
		AGFPlayerController* PlayerController = Cast<AGFPlayerController>(LocalController);
		AGFMainLobyPlayerController* LobyController = Cast<AGFMainLobyPlayerController>(LocalController);
		if (PlayerController)
		{
			PlayerController->ClientReceiveMessage(SenderName, TeamTagName, FullMessage, MessageType);
		}
		else if (LobyController)
		{
			LobyController->ClientReceiveMessage(SenderName, TeamTagName, FullMessage, MessageType);
		}
	}
}






void AGFBaseGameState::OnRep_CaptureGauge()
{
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		if (AGFPlayerController* GFPC = Cast<AGFPlayerController>(PC))
		{
			if (UGFCaptureStatusWidget* Widget = Cast<UGFCaptureStatusWidget>(GFPC->GetGFCaptureStatusWidget()))
			{
				Widget->UpdateGauge(CaptureGauge, CapturingTeam);
			}
		}
		
	}
}

void AGFBaseGameState::OnRep_CapturingTeam()
{
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		if (AGFPlayerController* GFPC = Cast<AGFPlayerController>(PC))
		{
			if (UGFCaptureStatusWidget* Widget = Cast<UGFCaptureStatusWidget>(GFPC->GetGFCaptureStatusWidget()))
			{
				Widget->UpdateGauge(CaptureGauge, CapturingTeam);
			}
		}

	}
}

float AGFBaseGameState::GetCaptureGauge() const
{
	return CaptureGauge;
}

void AGFBaseGameState::SetCaptureGauge(float InGauge)
{
	if (!HasAuthority())
		return;

	if (FMath::IsNearlyEqual(CaptureGauge, InGauge))
		return;

	CaptureGauge = InGauge;
	OnRep_CaptureGauge();
}

void AGFBaseGameState::SetCapturingTeam(FName InTeamName)
{
	if (!HasAuthority())
		return;

	if (CapturingTeam == InTeamName)
		return;

	CapturingTeam = InTeamName;
	OnRep_CapturingTeam();
}

void AGFBaseGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGFBaseGameState, CaptureGauge);
	DOREPLIFETIME(AGFBaseGameState, CapturingTeam);
}