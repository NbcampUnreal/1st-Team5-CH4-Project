#include "GFBaseCharacter.h"
#include "EnhancedInputComponent.h"
#include "GFPlayerController.h"
#include "Widget/ChatWidget/GFChatWidget.h"
#include "Shop/GFApple.h"
#include "Shop/GFBanana.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Component/MultiplayerEventsManager/GFMultiplayerEventsManager.h"
#include "TimerManager.h"

AGFBaseCharacter::AGFBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bIsStunned = false;

}

void AGFBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGFBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString AGFBaseCharacter::GetTeamTagName()
{
	// 이미 액터에 부착된 컴포넌트 목록에서 찾기
	TArray<UActorComponent*> Components;
	GetComponents(Components);
	for (UActorComponent* Comp : Components)
	{
		if (Comp && Comp->GetClass()->GetName().Contains(TEXT("BPC_MultiplayerEventsManager")))
		{
			TObjectPtr<UGFMultiplayerEventsManager> MulitPlayerComponent = Cast<UGFMultiplayerEventsManager>(Comp);
			if (MulitPlayerComponent)
			{
				return MulitPlayerComponent->GetCurrentTeamTagName();
			}
		}
	}

	return "Error";
}

void AGFBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput
		= Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (AGFPlayerController* PlayerController
			= Cast<AGFPlayerController>(GetController()))
		{
			if (PlayerController->FocusChatChatAction)
			{
				EnhancedInput->BindAction(PlayerController->FocusChatChatAction
					, ETriggerEvent::Triggered
					,this
					, &AGFBaseCharacter::FocusChatInputBox);
			}
		}
	}
}

void AGFBaseCharacter::FocusChatInputBox(const FInputActionValue& Value)
{
	if (AGFPlayerController* PlayerController = Cast<AGFPlayerController>(GetController()))
	{
		if (TObjectPtr<UGFChatWidget> ChatWidget = PlayerController->GetChatWidget())
		{
			if (ChatWidget->ChatInputBox)
			{
				PlayerController->SetInputMode(FInputModeUIOnly());
				PlayerController->bShowMouseCursor = true;
				ChatWidget->SetChatInputBoxFocus();
			}
		}
	}
}

void AGFBaseCharacter::PickUpItem(AActor* Item)
{
	if (Item)
	{
		if (AGFApple* Apple = Cast<AGFApple>(Item))
		{
			Apple->PickUp(this);
			HeldItem = Item;
		}
		else if (AGFBanana* Banana = Cast<AGFBanana>(Item))
		{
			Banana->PickUp(this);
			HeldItem = Item;
		}
	}
}

void AGFBaseCharacter::ThrowHeldItem()
{
	if (HeldItem)
	{
		// 던지는 힘을 설정 캐릭터 전방으로 던지기
		FVector ThrowDirection = GetActorForwardVector();
		float ThrowForce = 2000.0f; // 원하는 값으로 조정

		if (AGFApple* Apple = Cast<AGFApple>(HeldItem))
		{
			Apple->Throw(ThrowDirection * ThrowForce);
		}
		else if (AGFBanana* Banana = Cast<AGFBanana>(HeldItem))
		{
			Banana->Throw(ThrowDirection * ThrowForce);
		}

		HeldItem = nullptr;
	}
}

// 스턴 적용
void AGFBaseCharacter::ApplyStun(float Duration)
{
	if (!bIsStunned)
	{
		bIsStunned = true;

		// 캐릭터의 움직임을 완전히 비활성화 (DisableMovement)
		if (GetCharacterMovement())
		{
			GetCharacterMovement()->DisableMovement();
		}

		// 일정 시간 후 스턴 해제를 위한 타이머 설정
		if (GetWorld())
		{
			GetWorld()->GetTimerManager().SetTimer(StunTimerHandle, this, &AGFBaseCharacter::EndStun, Duration, false);
		}

		UE_LOG(LogTemp, Log, TEXT("Character is stunned for %f seconds"), Duration);
	}
}

// 스턴 해제: 이동 복구
void AGFBaseCharacter::EndStun()
{
	bIsStunned = false;

	if (GetCharacterMovement())
	{
		// 기본 이동 모드로 복구 (예: 걷기)
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	}

	UE_LOG(LogTemp, Log, TEXT("Stun ended"));
}
