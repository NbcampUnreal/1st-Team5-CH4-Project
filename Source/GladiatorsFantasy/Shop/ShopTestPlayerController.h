
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "ShopTestPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class GLADIATORSFANTASY_API AShopTestPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AShopTestPlayerController();

protected:
	virtual void BeginPlay() override;

	// InputComponent가 초기화될 때 호출됨
	virtual void SetupInputComponent() override;

	// 던지기 액션 처리 함수
	void HandleThrowAction(const FInputActionValue& Value);

	// 입력 매핑 컨텍스트를 할당할 변수 (에디터 또는 생성자에서 지정)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* InputMappingContext;

	// 던지기 액션 Input Action (에디터 또는 생성자에서 지정)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* ThrowAction;
};
