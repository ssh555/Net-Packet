#pragma once
#include "nppch.h"
#include "INetSerializable.h"
#include "NetDataWriter.h"
#include "NetDataReader.h"

namespace NetPacket
{
	class Test : public INetSerializable
	{
	public:
		virtual void Serialize(NetDataWriter& writer) const override
		{
			// 开头必须有
			writer.Put(GetTypeHash());
		}

		virtual void Deserialize(NetDataReader& reader) override
		{
			// 开头必须有
			reader.PeekUShort();
		}

		static uint16_t GetTypeHash()
		{
			// 使用常量字符串作为类型标识符
			return MurmurHash16("Test");
		}
	};
}