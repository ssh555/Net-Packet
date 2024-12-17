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
			// ��ͷ������
			writer.Put(GetTypeHash());
		}

		virtual void Deserialize(NetDataReader& reader) override
		{
			// ��ͷ������
			reader.PeekUShort();
		}

		static uint16_t GetTypeHash()
		{
			// ʹ�ó����ַ�����Ϊ���ͱ�ʶ��
			return MurmurHash16("Test");
		}
	};
}