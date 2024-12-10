#pragma once
#include "nppch.h"
namespace NetPacket
{
	class NetDataWriter;
	class NetDataReader;

	// INetSerializable �ӿ�
	/*
		Packet = PacketSize(4�ֽ�) + ClientID(2�ֽ�) + TypeHashID(2�ֽ�) + ���л��ֽ�������
		PacketSize =  ClientID(2�ֽ�) +  TypeHashID(2�ֽ�) + ���л��ֽ�������
		�ܵ�Packet�ֽ��� = 4�ֽ� + PacketSize
	*/
	class NP_API INetSerializable
	{
	public:
		virtual ~INetSerializable() = default;

		virtual void Serialize(NetDataWriter& writer) const = 0;

		virtual void Deserialize(NetDataReader& reader) = 0;

		// 2�ֽ�
		virtual uint16_t GetTypeHash();
	};
};

