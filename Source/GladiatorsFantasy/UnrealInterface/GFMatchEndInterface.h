#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GFMatchEndInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGFMatchEndInterface : public UInterface
{
	GENERATED_BODY()
};

class GLADIATORSFANTASY_API IGFMatchEndInterface
{
	GENERATED_BODY()

	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DOMMatchEnd(); // DOM 전용 종료 처리
};
