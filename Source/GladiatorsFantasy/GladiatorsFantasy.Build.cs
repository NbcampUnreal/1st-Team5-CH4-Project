// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class GladiatorsFantasy : ModuleRules
{
	public GladiatorsFantasy(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "SlateCore", "Slate", "EnhancedInput", "AIModule", "GameplayTags", "LevelSequence", "MovieScene", "CinematicCamera" });

		PrivateDependencyModuleNames.AddRange(new string[] { "RiderLink", "OnlineSubsystem" });
		
		PublicIncludePaths.AddRange(new string[] { "GladiatorsFantasy" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
