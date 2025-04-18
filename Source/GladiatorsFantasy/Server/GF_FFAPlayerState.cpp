#include "Server/GF_FFAPlayerState.h"
#include "Net/UnrealNetwork.h"

int32 AGF_FFAPlayerState::TestPlayerIndex = 1;

void AGF_FFAPlayerState::AddKill()
{
	KillCount++;
}

int32 AGF_FFAPlayerState::GetKillCount() const
{
	return KillCount;
}

// 테스트용
void AGF_FFAPlayerState::BeginPlay()
{
    Super::BeginPlay();

 
    //if (HasAuthority())
    //{
    //    // 서버용 이름 할당
    //    FString GeneratedName = FString::Printf(TEXT("TestPlayer%d"), TestPlayerIndex++);
    //    SetPlayerCustomName(GeneratedName); // 부모 함수로 설정 (Replicate 대상)
    //}
}

void AGF_FFAPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGF_FFAPlayerState, KillCount);
}
