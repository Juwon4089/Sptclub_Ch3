// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Sptclub_Ch3 : ModuleRules
{
	public Sptclub_Ch3(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
