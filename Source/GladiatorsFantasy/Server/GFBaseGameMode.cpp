#include "Server/GFBaseGameMode.h"
#include "GameFramework/GameState.h"
#include "Server/GFBasePlayerState.h"
#include "Character/GFPlayerController.h"
#include "Kismet/GameplayStatics.h"

AGFBaseGameMode::AGFBaseGameMode()
{
    bAllPlayersReady = false;
}

FString AGFBaseGameMode::GetTargetMapName() const
{
    return TEXT("DefaultLevel"); // 기본값
}

// 나중에 경로 통일
void AGFBaseGameMode::TravelToAssignedLevel()
{

    //// 나중에 통일된 경로로 수정
    const FString BasePath = TEXT("/Game/WS/");
    FString LevelName = GetTargetMapName();
    FString FullPath = FString::Printf(TEXT("%s%s?listen"), *BasePath, *LevelName);
    FString ClientPath = BasePath + LevelName;

    FString NetAddress = GetServerAddress(); // ← 동적 주소
    FString ClientTravelURL = FString::Printf(TEXT("%s%s"), *NetAddress, *ClientPath);

    GetWorld()->ServerTravel(FullPath); // true 넣으면 절대 경로


    /*UGameplayStatics::OpenLevel(this, FName(*FullPath), true);

    FTimerHandle TravelDelayHandle;
    GetWorld()->GetTimerManager().SetTimer(
        TravelDelayHandle,
        [this, ClientTravelURL]() 
        {
            for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
            {
                if (APlayerController* PC = It->Get())
                {
                    if (AGFPlayerController* GFPC = Cast<AGFPlayerController>(PC))
                    {
                        GFPC->ClientTravelToMap(ClientTravelURL);
                    }
                }
            }
        },
        1.0f, 
        false
    );*/
    
}

void AGFBaseGameMode::TravelToAssignedLevelForBP(const FString& InLevelName)
{
    const FString BasePath = TEXT("/Game/WS/");
    FString LevelName = InLevelName;
    FString FullPath = FString::Printf(TEXT("%s%s?listen"), *BasePath, *LevelName);

    GetWorld()->ServerTravel(FullPath);
}

void AGFBaseGameMode::TarvelToLastLevel() const
{
    const FString LastLevelPath = TEXT("/Game/GY/TestLevel2.TestLevel2?listen");
    GetWorld()->ServerTravel(LastLevelPath);
}

FString AGFBaseGameMode::GetServerAddress()
{
    if (UNetDriver* NetDriver = GetWorld()->GetNetDriver())
    {
        return NetDriver->LowLevelGetNetworkNumber(); // 예: "127.0.0.1:7777"
    }
    return TEXT("127.0.0.1:7777"); // fallback -> PIE 전용
}

bool AGFBaseGameMode::AreAllPlayersReady()
{
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        APlayerController* PC = It->Get();
        if (!IsValid(PC) || !IsValid(PC->GetPawn()))
        {
            return false;
        }
    }
    return true;
}


void AGFBaseGameMode::ChangeLevel()
{
    for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
    {
        APlayerController* PC = Iterator->Get();
        if (PC)
        {
            AGFBasePlayerState* BPS = Cast<AGFBasePlayerState>(PC->PlayerState);
            if (BPS)
            {
                BPS->SaveToGameInstance();
            }
        }
    }
    AGFBaseGameMode* BaseGameMode = Cast<AGFBaseGameMode>(GetWorld()->GetAuthGameMode());
    BaseGameMode->TravelToAssignedLevel();
}

