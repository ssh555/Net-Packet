// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NetPacket : ModuleRules
{
    public NetPacket(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        PrivatePCHHeaderFile = "Public/nppch.h";

        PublicIncludePaths.AddRange(
            new string[] {
            }
            );
        PrivateIncludePaths.AddRange(
            new string[] {
                "NetPacket/Private",
                "NetPacket/Public",
            }
            );

        // 模块的公共依赖
        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
        });

        // 模块的私有依赖
        PrivateDependencyModuleNames.AddRange(new string[] {
            "CoreUObject",
            "Core",
            "InputCore",
            "Engine",
            "Slate",
            "SlateCore",
        });

        PublicDefinitions.Add("NP_UE_SUPPORT=1");


        DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
                "NetPacket",
            }
            );
    }
}
