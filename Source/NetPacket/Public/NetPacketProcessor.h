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
		// �������ݰ�����ȴ�����
		bool Receive(NetPackage* package);
		// ԭ������: packet size + client id + type hash + data
		bool Receive(uint8_t* data, int32_t size);

		// �������ж����е����ݰ�
		bool Process();

		// ��ȡ���л������ݰ�
		NetPackage* Serialize(INetSerializable* obj);

		// ע���Ӧ���͵Ľ��հ��ص�(����)
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
