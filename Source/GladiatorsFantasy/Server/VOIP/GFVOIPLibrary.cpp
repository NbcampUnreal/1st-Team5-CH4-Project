#include "Server/VOIP/GFVOIPLibrary.h"

void UGFVOIPLibrary::ClearVoicePackets(UObject* WorldContextObject)
{
	UWorld* const World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!IsValid(World))
	{
		return;
	}

	IOnlineVoicePtr VoiceInterface = Online::GetVoiceInterface(World);

	if (!VoiceInterface.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Clear voice packets couldn't get the voice interface!"));
	}

	VoiceInterface->ClearVoicePackets();
}
