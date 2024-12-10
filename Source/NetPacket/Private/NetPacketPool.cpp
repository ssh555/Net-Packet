#include "nppch.h"
#include "NetPacketPool.h"
#include "NetPacket.h"

const int32_t NetPacket::NetPacketPool::PacketPoolSize;

const int32_t NetPacket::NetPacketPool::InitPoolSize;

NetPacket::NetPacketPool::NetPacketPool() : _poolHead(nullptr), _poolCount(0), _poolEnd(nullptr)
{
	for (int32_t i = 0; i < InitPoolSize; ++i)
	{
		Recycle(new NetPackage());
	}
}

NetPacket::NetPacketPool::~NetPacketPool()
{
	std::lock_guard<std::mutex> lock(_poolLock);
	NetPackage* current = _poolHead;
	while (current != nullptr)
	{
		NetPackage* next = current->Next;
		delete current;
		current = next;
	}
	_poolHead = nullptr;
	_poolEnd = nullptr;
	_poolCount = 0;
}

int32_t NetPacket::NetPacketPool::PoolCount() const
{
	return _poolCount;
}

NetPacket::NetPackage* NetPacket::NetPacketPool::GetPacket(const uint8_t* data, int32_t start, int32_t length)
{
	NetPackage* package = InternalGetPacket(length);
	package->setRawData(data + start, length);
	return package;
}

NetPacket::NetPackage* NetPacket::NetPacketPool::GetPacket(int32_t size)
{
	return InternalGetPacket(size);
}

NetPacket::NetPackage* NetPacket::NetPacketPool::InternalGetPacket(int32_t size)
{
	if (size > NetPackage::MaxPacketSize)
	{
		return new NetPackage(size);
	}

	NetPackage* packet = nullptr;

	{
		std::lock_guard<std::mutex> lock(_poolLock);

		packet = _poolHead;
		if (packet == nullptr)
		{
			return new NetPackage(size);
		}

		_poolHead = _poolHead->Next;
		if (_poolHead == nullptr)
		{
			_poolEnd = nullptr;
		}
		_poolCount--;
	}

	packet->Next = nullptr;

	packet->resize(size);
	return packet;
}

void NetPacket::NetPacketPool::Recycle(NetPackage* packet)
{
	if (packet->m_size > NetPackage::MaxPacketSize || _poolCount >= PacketPoolSize)
	{
		delete packet;
		return;
	}


	{
		std::lock_guard<std::mutex> lock(_poolLock);

		packet->Next = nullptr;

		if (_poolEnd == nullptr)
		{
			_poolHead = packet;
			_poolEnd = packet;
		}
		else
		{
			_poolEnd->Next = packet;
			_poolEnd = packet;
		}

		_poolCount++;
	}
}
