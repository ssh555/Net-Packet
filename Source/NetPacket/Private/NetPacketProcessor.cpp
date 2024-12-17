#include "nppch.h"
#include "NetPacketProcessor.h"
#include "INetSerializable.h"
#include "NetPacket.h"

namespace NetPacket
{
	void NetPacketProcessor::Receive(NetPackage* package)
	{
		std::lock_guard<std::mutex> lock(m_queueLock);
		m_packagequeue.push(package);
	}

	void NetPacketProcessor::Receive(uint8_t* data, int32_t size)
	{
		std::lock_guard<std::mutex> lock(m_queueLock);
		NetPackage* package = m_pool.GetPacket(size);
		package->setRawData(data, size, true);
		m_packagequeue.push(package);
	}

	void NetPacketProcessor::Process()
	{
		std::lock_guard<std::mutex> lock(m_queueLock);
		while (!m_packagequeue.empty())
		{
			NetPackage* p = m_packagequeue.front();
			m_packagequeue.pop();

			// packet size
			p->GetData(&m_reader);
			// client id
			int16_t cid = p->GetClientID();
			// type hash
			uint16_t hashid = m_reader.PeekUShort(false);
			// process data
			if (IsRegister(hashid))
			{
				m_packetCallbackMap[hashid](cid, &m_reader);
			}
			// recycle
			m_pool.Recycle(p);
		}
	}

	NetPackage* NetPacketProcessor::Serialize(INetSerializable* obj)
	{
		m_writer.Reset();
		obj->Serialize(m_writer);
		NetPackage* p = m_pool.GetPacket(m_writer.Length());
		p->setData(&m_writer);
		return p;
	}

	void NetPacketProcessor::Unregister(uint16_t hashid)
	{
		std::lock_guard<std::mutex> lock(m_mapLock);
		m_packetCallbackMap.erase(hashid);
	}

	bool NetPacketProcessor::IsRegister(uint16_t hashid)
	{
		auto it = m_packetCallbackMap.find(hashid);
		return it != m_packetCallbackMap.end();
	}


}