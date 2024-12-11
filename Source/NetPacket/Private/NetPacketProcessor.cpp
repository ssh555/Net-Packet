#include "nppch.h"
#include "NetPacketProcessor.h"
#include "INetSerializable.h"
#include "NetPacket.h"

namespace NetPacket
{
	bool NetPacketProcessor::Receive(NetPackage* package)
	{
		if (m_queueLock.try_lock())
		{
			m_packagequeue.push(package);
			return true;
		}
		return false;
	}

	bool NetPacketProcessor::Receive(uint8_t* data, int32_t size)
	{
		if (m_queueLock.try_lock())
		{
			NetPackage* package = m_pool.GetPacket(size);
			package->setRawData(data, size, true);
			m_packagequeue.push(package);
			return true;
		}
		return false;
	}

	bool NetPacketProcessor::Process()
	{
		if (m_queueLock.try_lock())
		{
			while (!m_packagequeue.empty())
			{
				NetPackage* p = m_packagequeue.front();
				m_packagequeue.pop();

				// packet size
				p->GetData(&m_reader);
				// client id
				int16_t cid = p->GetClientID();
				// type hash
				uint16_t hashid = m_reader.PeekUShort();
				// process data
				if (IsRegister(hashid))
				{
					m_packetCallbackMap[hashid](cid, &m_reader);
				}
				// recycle
				m_pool.Recycle(p);
			}
			return true;
		}
		return false;
	}

	NetPackage* NetPacketProcessor::Serialize(INetSerializable* obj)
	{
		m_writer.Reset();
		obj->Serialize(m_writer);
		NetPackage* p = m_pool.GetPacket(m_writer.Length());
		p->setData(&m_writer);
		return p;
	}

	bool NetPacketProcessor::Register(uint16_t hashid, std::function<void(int16_t, NetDataReader*)> callback)
	{
		if(m_mapLock.try_lock())
		{
			m_packetCallbackMap[hashid] = std::move(callback);
			return true;
		}
		return false;
	}

	bool NetPacketProcessor::Unregister(uint16_t hashid)
	{
		if (m_mapLock.try_lock())
		{
			m_packetCallbackMap.erase(hashid);
			return true;
		}
		return false;
	}

	bool NetPacketProcessor::IsRegister(uint16_t hashid)
	{
		auto it = m_packetCallbackMap.find(hashid);
		return it != m_packetCallbackMap.end();
	}
}