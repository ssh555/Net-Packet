#pragma once
#include "nppch.h"
namespace NetPacket
{
	class UNetDataWriter;
	class UNetDataReader;

	// INetSerializable �ӿ�
	INTERFACE NP_API INetSerializable
	{
	public:
		virtual ~INetSerializable() = default;

		virtual void Serialize(UNetDataWriter& writer) const = 0;

		virtual void Deserialize(UNetDataReader& reader) = 0;
	};
};

