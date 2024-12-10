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

		// writer.Put(GetTypeHash());
		// ���ڿ�ͷ����������л�
		virtual void Serialize(NetDataWriter& writer) const = 0;

		// ������ʱû������hash���ڽ��յ���֮��ͨ�����ݰ�Э�鴦����Ѿ�����������hash��Ȼ���Զ������л�Ϊ��Ӧ������
		virtual void Deserialize(NetDataReader& reader) = 0;

		// 2�ֽ� type hash -> ��Serialize��ǰ��Ӧ�����л�2�ֽڵ�����hash�����Զ����ɴ���ʱ�Զ�����
		virtual uint16_t GetTypeHash() const;
	};
};

