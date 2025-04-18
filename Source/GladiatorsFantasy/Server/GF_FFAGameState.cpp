#include "Server/GF_FFAGameState.h"
#include "Server/GF_FFAPlayerState.h"
#include "GameFramework/PlayerState.h"

TArray<AGF_FFAPlayerState*> AGF_FFAGameState::GetTopKillers() const
{
    TArray<AGF_FFAPlayerState*> TopPlayers;
    int32 MaxKills = -1;

    for (APlayerState* PS : PlayerArray)
    {
        AGF_FFAPlayerState* FFAPlayer = Cast<AGF_FFAPlayerState>(PS);
        if (!FFAPlayer) continue;

        int32 Kills = FFAPlayer->GetKillCount();
        if (Kills > MaxKills)
        {
            MaxKills = Kills;
            TopPlayers.Empty(); // 새로운 최고 점수, 기존 플레이어 초기화
            TopPlayers.Add(FFAPlayer);
        }
        else if (Kills == MaxKills)
        {
            TopPlayers.Add(FFAPlayer); // 동점자 추가
        }
    }
    TopPlayers.Sort([](const AGF_FFAPlayerState& A, const AGF_FFAPlayerState& B)
        {
            return A.GetPlayerCustomName() < B.GetPlayerCustomName(); // 알파벳 기준 정렬
        }
    );

    return TopPlayers;
}
