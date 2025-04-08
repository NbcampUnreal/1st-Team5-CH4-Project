#include "Server/GFBaseGameMode.h"
#include "GameFramework/GameState.h"
#include "Server/GFBasePlayerState.h"

FString AGFBaseGameMode::GetTargetMapName() const
{
    return TEXT("DefaultLevel"); // 기본값
}

// 나중에 경로 통일
void AGFBaseGameMode::TravelToAssignedLevel()
{
    // 나중에 통일된 경로로 수정
    const FString BasePath = TEXT("/Game/WS/");
    FString LevelName = GetTargetMapName();
    FString FullPath = FString::Printf(TEXT("%s%s?listen"), *BasePath, *LevelName);

    GetWorld()->ServerTravel(FullPath, true);
}

