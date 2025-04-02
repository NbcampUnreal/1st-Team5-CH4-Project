#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GFBaseCharacter.generated.h"

struct FInputActionValue;

UCLASS()
class GLADIATORSFANTASY_API AGFBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AGFBaseCharacter();

protected:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION()
	void FocusChatInputBox(const FInputActionValue& Value);
	
public:	
	virtual void Tick(float DeltaTime) override;

};
