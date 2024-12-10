#pragma once
#include "nppch.h"
namespace NetPacket
{
	class NetDataWriter;
	class NetDataReader;

	// INetSerializable ½Ó¿Ú
	INTERFACE NP_API INetSerializable
	{
	public:
		virtual ~INetSerializable() = default;

		virtual void Serialize(NetDataWriter& writer) const = 0;

		virtual void Deserialize(NetDataReader& reader) = 0;
	};
};

