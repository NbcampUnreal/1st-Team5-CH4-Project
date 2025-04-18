#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GFCharacterSelectWidget.generated.h"

class UEditableText;
class UButton;

UCLASS()
class GLADIATORSFANTASY_API UGFCharacterSelectWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> NextBtn;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BackBtn;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> NickNameSetBtn;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableText> InputNickName;

	UFUNCTION()
	void PressedNextBtn();
	UFUNCTION()
	void PressedBackBtn();
	UFUNCTION()
	void PressedNickNameSetBtn();
	UFUNCTION()
	void OnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);

	void ConnectServer();
};
