#include "nppch.h"
#include "NetPacket.h"

#if NP_UE_SUPPORT
// Copyright Epic Games, Inc. All Rights Reserved.

#include "NetPacket.h"

#define LOCTEXT_NAMESPACE "FNetPacketModule"

void FNetPacketModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FNetPacketModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FNetPacketModule, NetPacket)
#endif

#include "NetDataWriter.h"
#include "NetDataReader.h"
#include "NetPacketPool.h"
#include "FastBitConverter.h"

const int32_t NetPacket::NetPackage::MaxPacketSize = 2048;

// 预留6字节数据: PacketSize(4字节) + ClientID(2字节)
const int32_t NetPacket::NetPackage::HeaderSize = 6;

NetPacket::NetPackage::NetPackage(uint32_t maxSize) : MaxSize(maxSize), RawData(new uint8_t[maxSize]), m_size(0), Next(nullptr)
{
	memset(RawData, 0, MaxSize);
	// 只能在Pool new ，所以在pool加入
}

NetPacket::NetPackage::~NetPackage()
{
	delete RawData;
	RawData = nullptr;
	// 在pool移除
}

void NetPacket::NetPackage::resize(int32_t size)
{
	if (size + HeaderSize > MaxSize)
	{
		MaxSize = size;
		delete[] RawData;
		RawData = new uint8_t[MaxSize];
		m_size = 0;
	}
}

void NetPacket::NetPackage::setData(NetDataWriter* writer)
{
	setRawData(writer->Data(), writer->Length(), false);
}

void NetPacket::NetPackage::GetData(NetDataReader* reader)
{
	if (reader == nullptr)
	{
		return;
	}
	reader->SetSource(RawData + HeaderSize, m_size);
	// 不在这儿调用，统一在NetPacketProcessor中Process Packet 后统一调用全部回归对象池
	// 回归对象池
	//if (pool)
	//{
	//	pool->Recycle(this);
	//}
}

int16_t NetPacket::NetPackage::GetClientID() const
{
	int16_t id;
	memcpy(&id, RawData + 4, sizeof(int16_t));
	return id;
}

const uint8_t* NetPacket::NetPackage::getRawData() const
{
	return RawData;
}

void NetPacket::NetPackage::setRawData(const uint8_t* data, const int32_t size, bool bWithHeader)
{
	if (bWithHeader)
	{
		if (size > MaxSize)
		{
			MaxSize = size;
			delete[] RawData;
			RawData = new uint8_t[MaxSize];
		}
		memset(RawData, 0, MaxSize);
		memcpy(RawData, data, size);
		return;
	}
	if (size + HeaderSize > MaxSize)
	{
		MaxSize = size;
		delete[] RawData;
		RawData = new uint8_t[MaxSize];
	}
	memset(RawData, 0, MaxSize);
	memcpy(RawData + HeaderSize, data, size);
	this->m_size = size;
	// 设置数据包长度和ClientID
	FastBitConverter::GetBytes(RawData, 0, this->m_size);
	FastBitConverter::GetBytes(RawData, 4, (int16_t)0);

}

int32_t NetPacket::NetPackage::getSize() const
{
	return m_size;
}

int32_t NetPacket::NetPackage::getMaxSize() const
{
	return MaxSize;
}

