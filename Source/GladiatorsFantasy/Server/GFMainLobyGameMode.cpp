#include "Server/GFMainLobyGameMode.h"
#include "Server/GFBasePlayerState.h"

FString AGFMainLobyGameMode::GetTargetMapName() const
{
    return TEXT("TestLevel1");
}

void AGFMainLobyGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
    if (!Options.Contains(TEXT("allowConnect")))
    {
        ErrorMessage = TEXT("접속 허용 옵션이 없습니다. 버튼을 눌러 접속을 시도해주세요.");
        return;
    }
    
    Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
}


void AGFMainLobyGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    UE_LOG(LogTemp, Warning, TEXT("==== 접속한 컨트롤러 %s ===="), *NewPlayer->GetName());
    AGFBasePlayerState* GFPS = Cast<AGFBasePlayerState>(NewPlayer->PlayerState);
    if (GFPS)
    {
        GFPS->SetMoney(1000);
        GFPS->SetWinPoint(0);
        UE_LOG(LogTemp, Warning, TEXT("==== 접속한 닉네임 %s ===="), *GFPS->GetPlayerCustomName());
    }
}
