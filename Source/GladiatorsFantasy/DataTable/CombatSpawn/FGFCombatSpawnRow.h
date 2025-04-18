#pragma once

#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "FGFCombatSpawnRow.generated.h"

USTRUCT(BlueprintType)
struct FCombatCharacterData : public FTableRowBase
{
    GENERATED_BODY()

    // 블루프린트의 식별 이름
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString CharacterBPName;

    // 표시용 이름 (선택 사항)
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText DisplayName;

    // 실제 스폰할 클래스
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<ACharacter> CharacterClass;
};