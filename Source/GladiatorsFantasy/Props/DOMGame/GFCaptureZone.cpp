#include "Props/DOMGame/GFCaptureZone.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Character/GFBaseCharacter.h"
#include "Server/GFBaseGameState.h"
#include "Widget/DOMGameWidget/GFCaptureStatusWidget.h"
#include "UnrealInterface/GFMatchEndInterface.h"

AGFCaptureZone::AGFCaptureZone()
{
    PrimaryActorTick.bCanEverTick = false;

    CaptureBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CaptureBox"));
    RootComponent = CaptureBox;

    CaptureBox->SetCollisionProfileName(TEXT("Trigger"));
    CaptureBox->OnComponentBeginOverlap.AddDynamic(this, &AGFCaptureZone::OnOverlapBegin);
    CaptureBox->OnComponentEndOverlap.AddDynamic(this, &AGFCaptureZone::OnOverlapEnd);
}

void AGFCaptureZone::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority()) // 서버 전용
    {
        LastEvaluateTime = GetWorld()->GetTimeSeconds();

        GetWorldTimerManager().SetTimer(
            CaptureEvaluationTimer,
            this,
            &AGFCaptureZone::EvaluateCaptureStatus,
            0.1f,
            true
        );
    }
}

void AGFCaptureZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (ACharacter* Character = Cast<ACharacter>(OtherActor))
    {
        PlayersInZone.Add(Character);
    }
}

void AGFCaptureZone::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (ACharacter* Character = Cast<ACharacter>(OtherActor))
    {
        PlayersInZone.Remove(Character);
    }
}

void AGFCaptureZone::EvaluateCaptureStatus()
{
    const float CurrentTime = GetWorld()->GetTimeSeconds();
    const float DeltaTime = CurrentTime - LastEvaluateTime;
    LastEvaluateTime = CurrentTime;

    TMap<FName, int32> TeamCounts;

    for (AActor* Actor : PlayersInZone)
    {
        if (AGFBaseCharacter* GFCharacter = Cast<AGFBaseCharacter>(Actor))
        {
            FString TeamTag = GFCharacter->GetTeamTagName();

            if (TeamTag == "Teams.TeamA")
                TeamCounts.FindOrAdd("TeamA")++;
            else if (TeamTag == "Teams.TeamB")
                TeamCounts.FindOrAdd("TeamB")++;
        }
    }

    // 초기값
    float NewGauge = 50.f;
    FName NewCapturingTeam = NAME_None;

    if (AGFBaseGameState* GS = GetWorld()->GetGameState<AGFBaseGameState>())
    {
        NewGauge = GS->GetCaptureGauge(); // 현재 값을 기준으로 계산

        if (TeamCounts.Num() == 1)
        {
            FName SingleTeam = TeamCounts.begin().Key();
            float Change = CaptureRatePerSecond * DeltaTime;

            if (SingleTeam == "TeamA")
                NewGauge = FMath::Clamp(NewGauge - Change, 0.f, 100.f);
            else if (SingleTeam == "TeamB")
                NewGauge = FMath::Clamp(NewGauge + Change, 0.f, 100.f);

            NewCapturingTeam = SingleTeam;
        }
        else
        {
            NewCapturingTeam = NAME_None;
        }

        // GameState에 결과 전달
        GS->SetCaptureGauge(NewGauge);
        GS->SetCapturingTeam(NewCapturingTeam);

        if (GS->GetCaptureGauge() <= 0.f || GS->GetCaptureGauge() >= 100.f)
        {
            if (GS->GetClass()->ImplementsInterface(UGFMatchEndInterface::StaticClass()))
            {
                IGFMatchEndInterface::Execute_DOMMatchEnd(GS);
            }
        }
    }

    LogPlayerTeamInfo(TeamCounts, NewGauge);

}



void AGFCaptureZone::LogPlayerTeamInfo(const TMap<FName, int32>& TeamCounts, float GaugeToPrint)
{
    for (const auto& Entry : TeamCounts)
    {
        UE_LOG(LogTemp, Warning, TEXT("Team %s: %d"), *Entry.Key.ToString(), Entry.Value);
    }

    UE_LOG(LogTemp, Warning, TEXT("Capture Gauge: %.2f"), GaugeToPrint);
}
