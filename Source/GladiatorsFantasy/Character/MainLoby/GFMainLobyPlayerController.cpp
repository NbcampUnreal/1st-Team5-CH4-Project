#include "Character/MainLoby/GFMainLobyPlayerController.h"

#include "CineCameraActor.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "LevelSequencePlayer.h"
#include "MovieSceneSequencePlaybackSettings.h"
#include "Blueprint/UserWidget.h"
#include "DataTable/LobbySpawn/FLobbySpawnRow.h"
#include "Kismet/GameplayStatics.h"
#include "Props/LobbyPlayerSlot/GFLobbyPlayerSlot.h"
#include "Props/SelectActor/SelectActor.h"
#include "Server/GFBasePlayerState.h"
#include "Widget/MainLobyWidget/GFMainLobyWidget.h"
#include "Widget/CharacterSelectWidget/GFCharacterSelectWidget.h"
#include "Widget/LobyWidget/GFLobyWidget.h"
#include "Widget/ChatWidget/GFChatWidget.h"

AGFMainLobyPlayerController::AGFMainLobyPlayerController()
{
	bReplicates = true;
}

void AGFMainLobyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = Cast<APlayerController>(this))
	{
		if (ULocalPlayer* LocalPlayer = PC->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
				ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
			{
				if (nullptr != LobyMappingContext)
				{
					Subsystem->AddMappingContext(LobyMappingContext, 0);
				}
			}
		}
	}
	
	if (IsLocalController())
	{
		MainLobyWidget = CreateWidget<UGFMainLobyWidget>(this, MainLobyWidgetClass);
		if (MainLobyWidget)
		{
			MainLobyWidget->AddToViewport();
		}
		
		CharacterSelectWidget = CreateWidget<UGFCharacterSelectWidget>(this, CharacterSelectWidgetClass);
		LobyWidget = CreateWidget<UGFLobyWidget>(this, LobyWidgetClass);
		//ChatWidget = CreateWidget<UGFChatWidget>(this, ChatWidgetClass);
	}

	TArray<AActor*> FoundCameras;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACineCameraActor::StaticClass(), FoundCameras);
	for (int i = 0; i < FoundCameras.Num(); i++)
	{
		if (FoundCameras[i]->ActorHasTag(TEXT("MainCam")))
		{
			MainCamera = Cast<ACineCameraActor>(FoundCameras[i]);
			break;
		}
	}

	FMovieSceneSequencePlaybackSettings PlayBackSetting;
	PlayBackSetting.bPauseAtEnd = true;
	MainLobyToLobySequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), MainLobyToLobySequence, PlayBackSetting, MainLobyToLobySequenceActor);
	MainLobyToLobySequencePlayer->OnFinished.AddDynamic(this, &AGFMainLobyPlayerController::OnSequenceFinished);
	
	FMovieSceneSequencePlaybackSettings PlayBackSettingTest;
	PlayBackSettingTest.bPauseAtEnd = true;
	SelectCharacterToWaitRoomSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), SelectCharacterToWaitRoomSequence, PlayBackSettingTest, SelectCharacterToWaitRoomSequenceActor);
	SelectCharacterToWaitRoomSequencePlayer->OnFinished.AddDynamic(this, &AGFMainLobyPlayerController::OnSequenceFinished);

	if (MainCamera)
	{
		SetViewTarget(MainCamera);
	}

	bShowMouseCursor = true;
	SetInputMode(FInputModeGameAndUI());
}

// ========================================
// 입력 처리
// ========================================
void AGFMainLobyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// 예: MyAction이라는 UInputAction*를 사전에 생성해두고 바인딩합니다.
		EnhancedInputComp->BindAction(SelectAction, ETriggerEvent::Started, this, &AGFMainLobyPlayerController::SelectActionTriggered);
	}
}

void AGFMainLobyPlayerController::SelectActionTriggered()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

	if (HitResult.bBlockingHit)
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor)
		{
			ASelectActor* SelectActor = Cast<ASelectActor>(HitActor);
			if (SelectActor)
			{
				// 예: 무기라면 무기 선택 처리
				if (SelectActor->ActorHasTag("Weapon"))
				{
					// 무기 선택 로직
					if (PrevSelectedWeapon)
					{
						PrevSelectedWeapon->ToggleOverlayMaterial(false);
					}
					PrevSelectedWeapon = SelectActor;
					FString SelecTypeTest = SelectActor->GetSelectType();
					UE_LOG(LogTemp, Warning, TEXT("Clicked Actor: %s"), *SelecTypeTest);
					GetPlayerState<AGFBasePlayerState>()->SetFWeaponInfo(SelecTypeTest, EWeaponRarity::EWR_Nomal);
					SelectActor->ToggleOverlayMaterial(true);
				}
				else if (SelectActor->ActorHasTag("Character"))
				{
					// 캐릭터 선택 로직
					if (PrevSelectedCharacter)
					{
						// 이전 캐릭터는 Idle 실행
						PrevSelectedCharacter->PlayAnimIdle();
						PrevSelectedCharacter->ToggleOverlayMaterial(false);
					}
					PrevSelectedCharacter = SelectActor;
					FString SelecTypeTest = SelectActor->GetSelectType();
					UE_LOG(LogTemp, Warning, TEXT("Clicked Actor: %s"), *SelecTypeTest);
					GetPlayerState<AGFBasePlayerState>()->SetCharacterBPName(SelecTypeTest);
					SelectActor->ToggleOverlayMaterial(true);

					// 선택시 애니메이션 실행
					SelectActor->PlayAnimMontageSelect();
					
					// 서버한테 나 이걸로 변경할래 호출
					ChangeSelectedCharacter(SelecTypeTest);
					ChangeAnim(SelecTypeTest);
				}
			}
		}
	}
}

void AGFMainLobyPlayerController::ServerSetMesh_Implementation(const TSoftObjectPtr<USkeletalMesh>& InSkeletalMesh)
{
	// 비동기처리
	// if (SelectedCharacter == nullptr || !InSkeletalMesh.IsValid()) return;
	//
	// FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
	//
	// Streamable.RequestAsyncLoad(InSkeletalMesh.ToSoftObjectPath(), [=]()
	// {
	// 	USkeletalMesh* LoadedMesh = InSkeletalMesh.Get();
	//
	// 	if (LoadedMesh && SelectedCharacter && SelectedCharacter->SkeletalMeshCompo)
	// 	{
	// 		SelectedCharacter->SkeletalMeshCompo->SetSkeletalMesh(LoadedMesh);
	// 		ReplicatedMesh = LoadedMesh;
	// 	}
	// });

	// 동기 처리
	if (LobbySlot == nullptr) return;
	if (LobbySlot->SelectedCharacter == nullptr) return;

	USkeletalMesh* LoadedMesh = InSkeletalMesh.LoadSynchronous();

	if (LoadedMesh)
	{
		LobbySlot->SelectedCharacter->SkeletalMeshCompo->SetSkeletalMesh(LoadedMesh);
		LobbySlot->ReplicatedMesh = LoadedMesh;
	}
}

void AGFMainLobyPlayerController::ServerSetAnim_Implementation(const TSoftObjectPtr<UAnimSequence>& InAnimSequence)
{
	if (LobbySlot == nullptr) return;
	if (LobbySlot->SelectedCharacter == nullptr) return;

	UAnimSequence* LoadedAnimSequence = InAnimSequence.LoadSynchronous();

	if (LoadedAnimSequence)
	{
		LobbySlot->SelectedCharacter->SkeletalMeshCompo->SetAnimation(LoadedAnimSequence);
		LobbySlot->SelectedCharacter->SkeletalMeshCompo->PlayAnimation(LoadedAnimSequence, true);
		LobbySlot->ReplicatedAnim = LoadedAnimSequence;
	}
}

void AGFMainLobyPlayerController::ChangeSelectedCharacter(FString SelecTypeTest)
{
	AGameStateBase* GameState = GetWorld()->GetGameState();
	if (GameState)
	{
		AGFBaseGameState* GFGameState = Cast<AGFBaseGameState>(GameState);
		if (GFGameState)
		{
			FString ContextString = TEXT("DT_LobbyCharacterContext");
			FLobbyCharacterData* Row = GFGameState->DT_LobbyCharacter->FindRow<FLobbyCharacterData>(FName(SelecTypeTest), ContextString, true);
			if (Row)
			{
				ServerSetMesh(Row->SkeletalMesh);
			}
		}
	}
}

void AGFMainLobyPlayerController::ChangeAnim(FString SelecTypeTest)
{
	AGameStateBase* GameState = GetWorld()->GetGameState();
	if (GameState)
	{
		AGFBaseGameState* GFGameState = Cast<AGFBaseGameState>(GameState);
		if (GFGameState)
		{
			FString Key = SelecTypeTest;
			Key += LobbySlot->AnimType;
			
			FString ContextString = TEXT("DT_LobbyLocationContext");
			FLobbyLocationData* Row = GFGameState->DT_LobbyLocation->FindRow<FLobbyLocationData>(FName(Key), ContextString, true);
			if (Row)
			{
				ServerSetAnim(Row->Animation);
			}
		}
	}
}

// ================================================
// Chat Function
// ================================================
void AGFMainLobyPlayerController::ClientReceiveMessage_Implementation(const FString& SenderName, const FString& TeamTagName, const FString& Message, EMessage_Type MessageType)
{
	if (LobyWidget->GetChatUI())
	{
		if (MessageType == EMessage_Type::Team
			&& TeamTagName != GetTeamTagName())
		{
			return;
		}
		
		LobyWidget->GetChatUI()->UpdateChatLogBox(Message, MessageType);
	}
}

void AGFMainLobyPlayerController::ServerSendMessage_Implementation(const FString& Message, const FString& TeamTagName, EMessage_Type MessageType)
{
	TObjectPtr<AGFBaseGameState> BaseGameState = GetWorld()->GetGameState<AGFBaseGameState>();
	if (BaseGameState)
	{
		BaseGameState->BroadcastMessage(GetPlayerState<AGFBasePlayerState>()->GetPlayerCustomName(), TeamTagName, Message, MessageType);
	}
}

FString AGFMainLobyPlayerController::GetTeamTagName()
{
	// 다 개인이니까.. 음.. 고유 ID를 전달해주어도 괜찮을 것 같다.
	return "Single";
}

void AGFMainLobyPlayerController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGFMainLobyPlayerController, LobbySlot);
}

// ========================================
// UI 처리
// ========================================
void AGFMainLobyPlayerController::OnSequenceFinished()
{
	// 현재 켜져있는 에셋에 따라서 반대 UI를 실행해주어야 한다.
	switch (CurrentSequenceType)
	{
		case ESequenceType::MainToSelect:
			//MainLobyToLobySequencePlayer->Stop();
			ShowCharacterSelectWidget();
			break;

		case ESequenceType::SelectToMain:
			//MainLobyToLobySequencePlayer->Stop();
			ShowMainLobyWidget();
			break;

		case ESequenceType::SelectToWaitRoom:
			ShowLobyWidget();
			break;
		
		case ESequenceType::WaitRoomToSelect :
			ShowCharacterSelectWidget();
			break;
		
		default:
			break;
	}
	
}

void AGFMainLobyPlayerController::ShowCharacterSelectWidget()
{
	if (IsLocalController())
	{
		if (CharacterSelectWidget)
		{
			CharacterSelectWidget->AddToViewport();
			CharacterSelectWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void AGFMainLobyPlayerController::ShowMainLobyWidget()
{
	if (IsLocalController())
	{
		if (MainLobyWidget)
		{
			MainLobyWidget->AddToViewport();
			MainLobyWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void AGFMainLobyPlayerController::ShowLobyWidget()
{
	if (IsLocalController())
	{
		if (LobyWidget)
		{
			LobyWidget->AddToViewport();
			LobyWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void AGFMainLobyPlayerController::PlaySequnceSelectCharacterToMain()
{
	if (MainLobyToLobySequence)
	{
		if (MainLobyToLobySequencePlayer)
		{
			MainLobyToLobySequencePlayer->PlayReverse();
		}
	}
}

void AGFMainLobyPlayerController::PlaySequnceMainToSelectCharacter()
{
	if (MainLobyToLobySequence)
	{
		if (MainLobyToLobySequencePlayer)
		{
			MainLobyToLobySequencePlayer->Play();
		}
	}
}

void AGFMainLobyPlayerController::PlaySelectCharacterToWaitRoom()
{
	if (SelectCharacterToWaitRoomSequence)
	{
		if (SelectCharacterToWaitRoomSequencePlayer)
		{
			SelectCharacterToWaitRoomSequencePlayer->Play();
		}
	}
}

void AGFMainLobyPlayerController::PlayWaitRoomToSelectCharacter()
{
	if (SelectCharacterToWaitRoomSequence)
	{
		if (SelectCharacterToWaitRoomSequencePlayer)
		{
			SelectCharacterToWaitRoomSequencePlayer->PlayReverse();
		}
	}
}

void AGFMainLobyPlayerController::StopMainLobyToLobySequencePlayer()
{
	if (MainLobyToLobySequencePlayer)
	{
		MainLobyToLobySequencePlayer->Stop();
	}
}

void AGFMainLobyPlayerController::StopSelectCharacterToWaitRoomSequencePlayer()
{
	if (SelectCharacterToWaitRoomSequencePlayer)
	{
		SelectCharacterToWaitRoomSequencePlayer->Stop();
	}
}