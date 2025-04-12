#include "Server/GFMainLobyGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "Props/LobbyPlayerSlot/GFLobbyPlayerSlot.h"
#include "Server/GFBasePlayerState.h"

AGFMainLobyGameMode::AGFMainLobyGameMode()
    : IsSetPlayerSlotsDone(false)
{
}

FString AGFMainLobyGameMode::GetTargetMapName() const
{
    return TEXT("TestLevel1");
}

void AGFMainLobyGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
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
    
    for (int i = 0; i < PlayerSlots.Num(); ++i)
    {
        if (!PlayerSlots[i]->GetPC())
        {
            PlayerSlots[i]->AddSelectedActor(NewPlayer);
            break;
        }
    }
}

void AGFMainLobyGameMode::BeginPlay()
{
    Super::BeginPlay();

    SetPlayerSlot();

    PlayerSlots[0]->AddSelectedActor(GetWorld()->GetFirstPlayerController());
}

void AGFMainLobyGameMode::Logout(AController* Exiting)
{
    Super::Logout(Exiting);


    APlayerController* PlayerController = Cast<APlayerController>(Exiting);
    if (PlayerController)
    {
        for (int i = 0; i < PlayerSlots.Num(); ++i)
        {
            if (PlayerSlots[i]->GetPC() == PlayerController)
            {
                PlayerSlots[i]->RemoveSelectedActor();
            }
        }
    }
}

void AGFMainLobyGameMode::SetPlayerSlot()
{
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGFLobbyPlayerSlot::StaticClass(), FoundActors);

    for (int i = 0; i < FoundActors.Num(); ++i)
    {
        PlayerSlots.Add(Cast<AGFLobbyPlayerSlot>(FoundActors[i]));
    }
    
    IsSetPlayerSlotsDone = true;
}