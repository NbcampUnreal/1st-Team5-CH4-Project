#include "Server/GFMainLobyGameMode.h"
#include "Server/GFBasePlayerState.h"

FString AGFMainLobyGameMode::GetTargetMapName() const
{
    return TEXT("TestLevel1");
}

void AGFMainLobyGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    AGFBasePlayerState* GFPS = Cast<AGFBasePlayerState>(NewPlayer->PlayerState);
    if (GFPS)
    {
        GFPS->SetMoney(1000);
        GFPS->SetWinPoint(0);
    }
}

