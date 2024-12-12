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
		// writer.Put(GetTypeHash());
		// 先在开头进行这个序列化
		// 递归序列化也会序列化hash
		virtual void Serialize(NetDataWriter& writer) const = 0;

		// 先调用reader.PeekUShort()弹出hash
		virtual void Deserialize(NetDataReader& reader) = 0;

		// 2字节 type hash -> 在Serialize最前面应该序列化2字节的类型hash，在自动生成代码时自动加入
		virtual uint16_t GetTypeHash() const;
	};
};

