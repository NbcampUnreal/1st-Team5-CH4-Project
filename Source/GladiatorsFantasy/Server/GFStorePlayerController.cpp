#include "Server/GFStorePlayerController.h"
#include "Shop/GFShop.h"
#include "Server/GFStoreGameMode.h"
#include "Server/GFStorePlayerState.h"

void AGFStorePlayerController::ClientShowStoreUI_Implementation()
{
	if (StoreWidget || !IsLocalController()) return;

	if (GetWorld() && GetWorld()->GetAuthGameMode())
	{
		AGFStoreGameMode* GM = Cast<AGFStoreGameMode>(GetWorld()->GetAuthGameMode());
		if (GM && GM->StoreWidgetClass)
		{
			StoreWidget = CreateWidget<UGFShop>(this, GM->StoreWidgetClass);
			if (StoreWidget)
			{
				StoreWidget->AddToViewport();
			}
		}
	}

}

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
	}
}
