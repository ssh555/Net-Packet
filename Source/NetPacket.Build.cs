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
            "Engine"
        });

        // �����Ҫ֧�ֲ���ڱ༭��ģʽ�����У������ Editor ģ��
        if (Target.bBuildEditor)
        {
            }

    }
}
