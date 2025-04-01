#include "AI/GFAIController.h"
#include "Server/GF_FFAGameMode.h"
#include "Kismet/GameplayStatics.h"

void AGFAIController::OnAIDeath()
{
	GetWorldTimerManager().SetTimer(
		RespawnTimerHandle,
		this,
		&AGFAIController::RequestRespawn,
		5.0f,
		false
	);
}

void AGFAIController::RequestRespawn()
{
	AGF_FFAGameMode* GM = Cast<AGF_FFAGameMode>(UGameplayStatics::GetGameMode(this));
	if (GM)
	{
		GM->SpawnAI();
	}

	Destroy();
}
