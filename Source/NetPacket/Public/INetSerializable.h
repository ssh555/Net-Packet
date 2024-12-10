#pragma once
#include "nppch.h"
namespace NetPacket
{
	class NetDataWriter;
	class NetDataReader;

	// INetSerializable 接口
	/*
		Packet = PacketSize(4字节) + ClientID(2字节) + TypeHashID(2字节) + 序列化字节流数据
		PacketSize =  ClientID(2字节) +  TypeHashID(2字节) + 序列化字节流数据
		总的Packet字节数 = 4字节 + PacketSize
	*/
	class NP_API INetSerializable
	{
	public:
		virtual ~INetSerializable() = default;

		virtual void Serialize(NetDataWriter& writer) const = 0;

		virtual void Deserialize(NetDataReader& reader) = 0;

		// 2字节
		virtual uint16_t GetTypeHash();
	};
};

