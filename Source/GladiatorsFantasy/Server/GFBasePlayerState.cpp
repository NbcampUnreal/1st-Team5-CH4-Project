#include "GFBasePlayerState.h"
#include "GameInstance/GFGameInstance.h"
#include "Net/UnrealNetwork.h"

FString AGFBasePlayerState::GetPlayerUniqueId() const
{
    if (GetUniqueId().IsValid())
    {
        return GetUniqueId()->ToString(); // Online subsystem ID (ex: Steam)
    }
    else
    {
        return FString::FromInt(GetPlayerId()); // fallback: connection-based player id
    }
}

void AGFBasePlayerState::SaveToGameInstance()
{
    UGFGameInstance* GI = GetGameInstance<UGFGameInstance>();
    if (!GI) return;

    FString PlayerUniqueId = GetPlayerUniqueId();

    FPlayerData& Data = GI->PlayerDataMap.FindOrAdd(PlayerUniqueId);
    Data.PlayerCustomName = PlayerCustomName;
    Data.Money = Money;
    Data.WinPoint = WinPoint;
    Data.LossCount = LossCount;
}

void AGFBasePlayerState::LoadFromGameInstance()
{
    UGFGameInstance* GI = GetGameInstance<UGFGameInstance>();
    if (!GI) return;

    FString PlayerUniqueId = GetPlayerUniqueId();

    if (GI->PlayerDataMap.Contains(PlayerUniqueId))
    {
        const FPlayerData& Data = GI->PlayerDataMap[PlayerUniqueId];
        SetPlayerName(Data.PlayerCustomName);
        Money = Data.Money;
        WinPoint = Data.WinPoint;
        LossCount = Data.LossCount;
    }
}

FString AGFBasePlayerState::GetPlayerCustomName() const
{
    return PlayerCustomName;
}

int32 AGFBasePlayerState::GetMoney() const
{
    return Money;
}

int32 AGFBasePlayerState::GetWinPoint() const
{
    return WinPoint;
}

int32 AGFBasePlayerState::GetLossCount() const
{
    return LossCount;
}

void AGFBasePlayerState::SetPlayerCustomName(FString CustomName)
{
    PlayerCustomName = CustomName;
}

void AGFBasePlayerState::PostNetInit()
{
    Super::PostNetInit();

    // 안전한 시점에서! GameInstance 데이터 로드 -> 로비에서 로드하지 않도록 오버라이드 필요
    LoadFromGameInstance();

    if (GEngine)
    {
        FString DebugMsg = FString::Printf(TEXT("PostNetInit called for PlayerID: %s"), *GetPlayerUniqueId());
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, DebugMsg);
    }
}

void AGFBasePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AGFBasePlayerState, PlayerCustomName);
    DOREPLIFETIME(AGFBasePlayerState, Money);
    DOREPLIFETIME(AGFBasePlayerState, WinPoint);
    DOREPLIFETIME(AGFBasePlayerState, LossCount);
}
