#include "nppch.h"
#if NP_UE_SUPPORT
#include "NPUE.h"

void NetPacket::FNPUE::StartupModule()
{
	// �����ʼ��ʱ���߼�
	UE_LOG(LogTemp, Warning, TEXT("NPUEPlugin has started!"));
}

void NetPacket::FNPUE::ShutdownModule()
{
	// ����ر�ʱ���߼�
	UE_LOG(LogTemp, Warning, TEXT("NPUEPlugin is shutting down!"));
}
#endif