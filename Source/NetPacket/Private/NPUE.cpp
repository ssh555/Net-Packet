#include "nppch.h"
#if NP_UE_SUPPORT
#include "NPUE.h"

void NetPacket::FNPUE::StartupModule()
{
	// 插件初始化时的逻辑
	UE_LOG(LogTemp, Warning, TEXT("NPUEPlugin has started!"));
}

void NetPacket::FNPUE::ShutdownModule()
{
	// 插件关闭时的逻辑
	UE_LOG(LogTemp, Warning, TEXT("NPUEPlugin is shutting down!"));
}
#endif