#if WITH_ENGINE
#pragma once
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "NPUE.generated.h"

namespace NetPacket
{
	class FNPUE : public IModuleInterface
	{
		virtual void StartupModule() override;


		virtual void ShutdownModule() override;

	};

	IMPLEMENT_MODULE(FNPUE, NetPacket)
}
#endif