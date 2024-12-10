using UnrealBuildTool;

public class NetPakcet : ModuleRules
{
    public NetPakcet(ReadOnlyTargetRules Target) : base(Target)
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
            "Engine"
        });

        // 如果需要支持插件在编辑器模式下运行，请加入 Editor 模块
        if (Target.bBuildEditor)
        {
            }

    }
}
