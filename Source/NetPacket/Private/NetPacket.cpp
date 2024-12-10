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

const int32_t NetPacket::NetPackage::MaxPacketSize = 2048;
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
	if (size > MaxSize)
	{
		MaxSize = size;
		delete[] RawData;
		RawData = new uint8_t[MaxSize];
		m_size = 0;
	}
}

void NetPacket::NetPackage::setData(NetDataWriter* writer)
{
	setRawData(writer->Data(), writer->Length());
}

void NetPacket::NetPackage::GetData(NetDataReader* reader)
{
	if (reader == nullptr)
	{
		return;
	}
	reader->SetSource(RawData, m_size);
	// 回归对象池
	if (pool)
	{
		pool->Recycle(this);
	}
}

const uint8_t* NetPacket::NetPackage::getRawData() const
{
	return RawData;
}

void NetPacket::NetPackage::setRawData(const uint8_t* data, const int32_t size)
{
	if (size > MaxSize)
	{
		MaxSize = size;
		delete[] RawData;
		RawData = new uint8_t[MaxSize];
	}
	memset(RawData, 0, MaxSize);
	memcpy(RawData, data, size);
	this->m_size = size;
}

int32_t NetPacket::NetPackage::getSize() const
{
	return m_size;
}

int32_t NetPacket::NetPackage::getMaxSize() const
{
	return MaxSize;
}

