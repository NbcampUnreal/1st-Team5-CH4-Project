
#include "Shop/ShopTestPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "Character/GFBaseCharacter.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"

AShopTestPlayerController::AShopTestPlayerController()
{

}

void AShopTestPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Enhanced Input: 로컬 플레이어 서브시스템을 통해 입력 매핑 컨텍스트를 추가
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 1);
			}
		}
	}
}

void AShopTestPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Enhanced Input 컴포넌트를 사용해 액션 바인딩
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (ThrowAction)
		{
			EnhancedInput->BindAction(ThrowAction, ETriggerEvent::Triggered, this, &AShopTestPlayerController::HandleThrowAction);
		}
	}
}

void AShopTestPlayerController::HandleThrowAction(const FInputActionValue& Value)
{
	// 현재 소유하고 있는 Pawn이 캐릭터 타입이며 GFBaseCharacter인지를 확인합니다.
	if (APawn* AGFPawn = GetPawn())
	{
		if (AGFBaseCharacter* MyCharacter = Cast<AGFBaseCharacter>(AGFPawn))
		{
			MyCharacter->ThrowHeldItem();
		}
	}
}