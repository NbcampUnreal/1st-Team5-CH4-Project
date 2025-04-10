#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
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

	FString GetTeamTagName();

	// 현재 들고 있는 아이템 저장 (관중석 아이템)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup")
	AActor* HeldItem;

	// 아이템 픽업 함수
	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void PickUpItem(AActor* Item);

	// 아이템 던지기 함수
	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void ThrowHeldItem();

	//스턴함수
	UFUNCTION(BlueprintCallable, Category = "Stun")
	void ApplyStun(float Duration);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stun")
	bool bIsStunned;

	FTimerHandle StunTimerHandle;

	void EndStun();
};
