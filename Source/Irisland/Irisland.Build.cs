// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Irisland : ModuleRules
{
	public Irisland(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
				"Irisland/Public"
			}
			);


		PrivateIncludePaths.AddRange(
			new string[] {
				"Irisland/Private"
				// ... add other private include paths required here ...
			}
			);

		PrivateIncludePathModuleNames.AddRange(new string[] { "Settings" });
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Projects"
		// ... add other public dependencies that you statically link with here ... 
		});


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				// ... add private dependencies that you statically link with here ...	
			}
		);


		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
		);
	}
}