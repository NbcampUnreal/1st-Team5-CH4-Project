#pragma once

#include "CoreMinimal.h"
#include "FLobbySpawnRow.generated.h"

USTRUCT(BlueprintType)
struct FLobbyCharacterData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	FString CharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	TSoftObjectPtr<USkeletalMesh> SkeletalMesh;
};

USTRUCT(BlueprintType)
struct FLobbyLocationData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
	FString LocationKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
	TSoftObjectPtr<UAnimSequence> Animation;
};