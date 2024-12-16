#pragma once
#include "nppch.h"
#include "INetSerializable.h"
#include "NetDataWriter.h"
#include "NetDataReader.h"

namespace NetPacket
{
	class NP_API Test : public INetSerializable
	{
	public:
		int t;
	public:
		virtual void Serialize(NetDataWriter& writer) const override
		{
			// 开头必须有
			writer.Put(GetTypeHash());
			writer.Put(t);
		}

		virtual void Deserialize(NetDataReader& reader) override
		{
			// 开头必须有
			reader.PeekUShort();
			reader.Get(t);
		}
		virtual uint16_t GetTypeHash() const override
		{
			// 使用常量字符串作为类型标识符
			return MurmurHash16("Test");
		}
	};
}