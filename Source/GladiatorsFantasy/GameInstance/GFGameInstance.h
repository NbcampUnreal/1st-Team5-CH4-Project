
#pragma once

#include "CoreMinimal.h"
#include "AdvancedFriendsGameInstance.h"
#include "Weapon/GFWeaponBase.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "GFGameInstance.generated.h"

class AGF_FFAGameState;
class AGFBasePlayerState;
class AGF_FFAPlayerState;

USTRUCT(BlueprintType)
struct FWeaponInfo
{
    GENERATED_BODY()
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString WeaponName;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EWeaponRarity WeaponRarity = EWeaponRarity::EWR_Nomal;
    
};

// Player의 정보 저장
USTRUCT(BlueprintType)
struct FPlayerData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString PlayerCustomName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Money = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 WinPoint = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 LossCount = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString CharacterBPName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FWeaponInfo WeaponInfo; 

    EWeaponRarity GetWeaponRarity() const { return WeaponInfo.WeaponRarity; }
    FString GetWeaponName() const { return WeaponInfo.WeaponName; }
    void SetWeaponRarity(EWeaponRarity InRarity) { WeaponInfo.WeaponRarity = InRarity; }
    void SetWeaponName(FString InWeaponName) { WeaponInfo.WeaponName = InWeaponName; }
};

// 게임 상태를 정의하는 enum
UENUM(BlueprintType)
enum class EGameState : uint8
{
    EGS_MainMenu   UMETA(DisplayName = "Main Menu"),
    EGS_InGame     UMETA(DisplayName = "In Game"),
    EGS_GameOver   UMETA(DisplayName = "Game Over")
};

UCLASS()
class GLADIATORSFANTASY_API UGFGameInstance : public UAdvancedFriendsGameInstance
{
	GENERATED_BODY()

public:
    // 초기화 시 호출되는 함수
    virtual void Init() override;

    // Player 전체 정보 저장
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player")
    TMap<FString, FPlayerData> PlayerDataMap;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels")
    bool bIsLastLevel;

    // 통계 관련 변수들
    //플레이어 킬수 저장
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    TMap<FString, int32> PlayerKillCounts;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int32 LevelIndex;

    // Top Killers 저장
    UPROPERTY(BlueprintReadOnly, Category = "Stats")
    TArray<TObjectPtr<AGF_FFAPlayerState>> TopKillers;

    // 게임 상태 변경 및 조회 함수
    UFUNCTION(BlueprintCallable, Category = "State")
    void SetGameState(EGameState NewState);

    UFUNCTION(BlueprintCallable, Category = "State")
    EGameState GetGameState() const;

    //플레이어별 킬수 업데이트 함수
    UFUNCTION(BlueprintCallable, Category = "Stats")
    void UpdatePlayerKillCounts(const TArray<AGF_FFAPlayerState*>& PlayerStates);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    int32 GetTotalKillCount() const;

    // 통계 업데이트 및 조회용 함수들

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void AddWin(const FString& PlayerId);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void AddLoss(const FString& PlayerId);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    void SetLevelIndex(int32 NewLevelIndex);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    int32 GetLevelIndex() const;
    
    UFUNCTION(BlueprintCallable, Category = "Stats")
    void SetTopKillers(const TArray<AGF_FFAPlayerState*>& InTopKillers);

    UFUNCTION(BlueprintCallable, Category = "Stats")
    TArray<AGF_FFAPlayerState*> GetTopKillersFromInstance() const;

    UFUNCTION(BlueprintCallable)
    void LogPlayerData(FString CallerTag);

    // 각 스테이지별 구매 여부 저장
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop")
    TArray<bool> StagePurchaseStatus;

    int32 GetNextLevelIndex() const;
    void SetNextLevelIndex(int32 InIndex);
    void IncrementLevelIndex();

private:
    // 현재 게임 상태 저장 변수
    EGameState CurrentGameState;

    // 다음에 이동할 레벨의 인덱스를 저장하는 변수 (상점이 사용)
    int32 NextLevelIndex;

    // 테스트용
  public:
      // 세션 접속을 시도하는 함수 (버튼 클릭 등에서 호출)
      //UFUNCTION(BlueprintCallable, Category = "Network")
      //void JoinGame();
    
 //
 // private:
 //     // 세션 검색 완료 후 호출될 델리게이트 함수
 //     void OnFindSessionsComplete(bool bWasSuccessful);
 //     // 세션 접속 완료 후 호출될 델리게이트 함수
 //     void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
 //
 //     TSharedPtr<FOnlineSessionSearch> SessionSearch;
};
