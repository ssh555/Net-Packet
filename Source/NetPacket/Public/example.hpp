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
			// ��ͷ������
			writer.Put(GetTypeHash());
			writer.Put(t);
		}

		virtual void Deserialize(NetDataReader& reader) override
		{
			// ��ͷ������
			reader.PeekUShort();
			reader.Get(t);
		}
		virtual uint16_t GetTypeHash() const override
		{
			// ʹ�ó����ַ�����Ϊ���ͱ�ʶ��
			return MurmurHash16("Test");
		}
	};
}