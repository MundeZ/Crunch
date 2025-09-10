// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Crunch : ModuleRules
{
	public Crunch(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"EnhancedInput",
			"GameplayTags",
			"GameplayAbilities",
			"GameplayTasks",
			"UMG",
			"Slate",
			"SlateCore"
		});
	}
}