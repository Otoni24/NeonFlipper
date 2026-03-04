// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Flipper : ModuleRules
{
	public Flipper(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Niagara" });
	}
}
