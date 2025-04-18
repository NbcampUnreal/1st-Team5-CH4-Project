#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "GFMultiplayerEventsManager.generated.h"


UCLASS( Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GLADIATORSFANTASY_API UGFMultiplayerEventsManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
	FGameplayTag TestCurrentTeamTag;
	UPROPERTY(Replicated,EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer TestMultiplayerGameplayTagsContainer;
	
public:	
	UGFMultiplayerEventsManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	FString GetCurrentTeamTagName() { return TestCurrentTeamTag.ToString(); }
};
