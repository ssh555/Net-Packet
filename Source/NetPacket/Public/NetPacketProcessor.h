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

	class NP_API NetPacketProcessor
	{
	public:
		// �������ݰ�����ȴ�����
		void Receive(NetPackage* package);
		// ԭ������: packet size + client id + type hash + data
		void Receive(uint8_t* data, int32_t size, bool bWithHead = true);

		// �������ж����е����ݰ�
		void Process();

		// ��ȡ���л������ݰ�
		NetPackage* Serialize(INetSerializable* obj);

		// ע���Ӧ���͵Ľ��հ��ص�(����)
		// ��������
		// (clientID, ����)
		template<typename T>
		typename std::enable_if<std::is_base_of<INetSerializable, T>::value, void>::type
		Register(uint16_t hashid, std::function<void(int16_t, INetSerializable*)> callback);

		void Unregister(uint16_t hashid);

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

	template<typename T>
	typename std::enable_if<std::is_base_of<INetSerializable, T>::value, void>::type
	NetPacket::NetPacketProcessor::Register(uint16_t hashid, std::function<void(int16_t, INetSerializable*)> callback)
	{
		std::lock_guard<std::mutex> lock(m_mapLock);
		m_packetCallbackMap[hashid] = [callback](int16_t clienID, NetDataReader* reader)
		{
			// ���ɶ�Ӧ��ջ����
			T obj;
			obj.Deserialize(*reader);
			INetSerializable* p = static_cast<INetSerializable*>(&obj);
			callback(clienID, p);
		};
	}

}
