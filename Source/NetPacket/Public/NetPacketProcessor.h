#pragma once
#include "NetDataReader.h"
#include "NetDataWriter.h"
#include <queue>
#include <functional>
#include <unordered_map>
#include <mutex>
#include "NetPacketPool.h"


namespace NetPacket
{
	class NetDataReader;
	class NetDataWriter;
	class INetSerializable;
	class NetPackage;
	class NetPacketPool;

	class NetPacketProcessor
	{
	public:
		// 接收数据包放入等待队列
		bool Receive(NetPackage* package);
		// 原生数据: packet size + client id + type hash + data
		bool Receive(uint8_t* data, int32_t size);

		// 处理所有队列中的数据包
		bool Process();

		// 获取序列化的数据包
		NetPackage* Serialize(INetSerializable* obj);

		// 注册对应类型的接收包回调(覆盖)
		bool Register(uint16_t hashid, std::function<void(int16_t, NetDataReader*)> callback);

		bool Unregister(uint16_t hashid);

	private:
		NetDataWriter m_writer;
		NetDataReader m_reader;
		NetPacketPool m_pool;

		std::queue<NetPackage*> m_packagequeue;

		std::unordered_map<uint16_t, std::function<void(int16_t, NetDataReader*)>> m_packetCallbackMap;

		mutable std::mutex m_queueLock;
		mutable std::mutex m_mapLock;

		bool IsRegister(uint16_t hashid);
	};
}
