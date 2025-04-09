
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GFItemType.generated.h"

class UBoxComponent;

UCLASS()
class GLADIATORSFANTASY_API AGFItemType : public AActor
{
	GENERATED_BODY()
	
public:
	AGFItemType();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Spawner")
    TSubclassOf<AActor> AppleItemClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Spawner")
    TSubclassOf<AActor> BananaItemClass;

    // 아이템을 스폰할 위치
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Spawner")
    FVector SpawnLocation;

    // 아이템을 스폰할 회전값
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Spawner")
    FRotator SpawnRotation;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Spawner")
    UBoxComponent* SpawnBox;

    // 랜덤하게 아이템를 스폰하는 함수
    UFUNCTION(BlueprintCallable, Category = "Item Spawner")
    void SpawnRandomItem();
};
