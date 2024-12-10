using UnrealBuildTool;

public class NetPacket : ModuleRules
{
    public NetPacket(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[] {
            }
            );
        PrivateIncludePaths.AddRange(
            new string[] {
                "NetPacket/Private",
            }
            );
        PrivatePCHHeaderFile = "NetPacket/Public/nppch.h";

        // ģ��Ĺ�������
        PublicDependencyModuleNames.AddRange(new string[] { 
            "Core", 
            "CoreUObject", 
            "Engine", 
            "InputCore", 
        });

        // ģ���˽������
        PrivateDependencyModuleNames.AddRange(new string[] { 
            "CoreUObject",
            "Core",
            "InputCore",
            "Engine",
        });

        PublicDefinitions.Add("NP_UE_SUPPORT=1");
    }
}
