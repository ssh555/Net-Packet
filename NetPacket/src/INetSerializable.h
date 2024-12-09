#pragma once
#include "nppch.h"

#if WITH_EDITOR
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include NP_GENERATE(NetSerializable)
#endif

namespace NetPacket
{
	class UNetDataWriter;
	class UNetDataReader;

	// INetSerializable ½Ó¿Ú
	INTERFACE INetSerializable
	{
		NP_GENERATED_BODY()

	public:
		virtual ~INetSerializable() = default;

		virtual void Serialize(UNetDataWriter& writer) const = 0;
		virtual void Deserialize(UNetDataReader& reader) = 0;
	};
#if WITH_EDITOR
	NP_UINTERFACE(MinimalAPI)
	INTERFACE UNetSerializable : public UInterface
	{
		NP_GENERATED_BODY()
	}
#endif


};
	
