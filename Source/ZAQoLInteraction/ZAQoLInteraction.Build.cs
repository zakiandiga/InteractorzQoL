// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ZAQoLInteraction : ModuleRules
{
	public ZAQoLInteraction(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		if(Target.Type == TargetType.Editor)
		{
            PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "UMG",


                "AssetTools",
                "AssetRegistry",
                "UnrealEd",
                "KismetCompiler"

				// ... add private dependencies that you statically link with here ...	
			}
            );
        }
		else
        {
            PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "UMG"


				// ... add private dependencies that you statically link with here ...	
			}
            );
        }



        DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
