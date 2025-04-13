#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FGFStoreCharacterSpawnRow.generated.h"

USTRUCT(BlueprintType)
struct FGFStoreCharacterSpawnData : public FTableRowBase
{
	GENERATED_BODY()

	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	FString CharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	TSoftObjectPtr<USkeletalMesh> SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TSoftObjectPtr<UAnimSequence> Animation;
};