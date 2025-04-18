#pragma once

#include "CoreMinimal.h"
#include "Widget/ChatWidget/GFChatWidget.h"
#include "GameFramework/GameState.h"
#include "GFBaseGameState.generated.h"

enum class EMessage_Type : uint8;

UCLASS()
class GLADIATORSFANTASY_API AGFBaseGameState : public AGameState
{
	GENERATED_BODY()

public:
	AGFBaseGameState();
	
	UFUNCTION(NetMulticast,Reliable)
	void BroadcastMessage(const FString& SenderName, const FString& TeamTagName, const FString& Message, EMessage_Type MessageType = EMessage_Type::All);



	// == 점령전 변수 
	// 게이지 값 (0 ~ 100)
	UPROPERTY(ReplicatedUsing = OnRep_CaptureGauge, EditAnywhere, BlueprintReadOnly, Category = "Gauge")
	float CaptureGauge = 50.f;

	// 점령한 팀 이름
	UPROPERTY(ReplicatedUsing = OnRep_CapturingTeam, EditAnywhere, BlueprintReadOnly, Category = "Gauge")
	FName CapturingTeam = NAME_None;


	UFUNCTION()
	void OnRep_CaptureGauge();
	UFUNCTION()
	void OnRep_CapturingTeam();

	float GetCaptureGauge() const;
	void SetCaptureGauge(float InGauge);
	void SetCapturingTeam(FName InTeamName);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BaseSpawn|Property")
	UDataTable* DT_LobbyCharacter;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BaseSpawn|Property")
	UDataTable* DT_LobbyLocation;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};