#include "Server/GFStorePlayerController.h"
#include "Shop/GFShop.h"
#include "Server/GFStoreGameMode.h"
#include "Server/GFStorePlayerState.h"
#include "Server/GFStoreGameState.h"


void AGFStorePlayerController::ServerSetReady_Implementation(bool bReady)
{
	AGFStorePlayerState* PS = GetPlayerState<AGFStorePlayerState>();
	if (PS)
	{
		PS->SetIsReady(bReady);

		PS->SaveToGameInstance();

		// GameMode에 완료 여부 체크 요청
		AGFStoreGameMode* GM = GetWorld()->GetAuthGameMode<AGFStoreGameMode>();
		if (GM)
		{
			GM->CheckAllPlayersReady();
		}
		// 입력 무시
	}
	SetIgnoreMoveInput(true);
	SetIgnoreLookInput(true);
	ClientBlockInput(bReady);
}
void AGFStorePlayerController::ClientBlockInput_Implementation(bool bBlock)
{
	SetIgnoreMoveInput(bBlock);
	SetIgnoreLookInput(bBlock);
}


void AGFStorePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController())
	{
		StoreWidget = CreateWidget<UGFShop>(this, StoreWidgetClass);
		StoreWidget->AddToViewport();
	}
}

