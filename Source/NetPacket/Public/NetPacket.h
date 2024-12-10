#if NP_UE_SUPPORT
// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FNetPacketModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

#endif

namespace NetPacket
{
	class NetDataReader;
	class NetDataWriter;

	class NetPackage {
		// 添加对象池的友元
		friend class NetPacketPool;
	public:
		static const int32_t MaxPacketSize;

	private:
		// 设置数据包大小
		NetPackage(uint32_t maxSize = 1024);
		~NetPackage();

		NetPackage* Next;
		NetPacketPool* pool;
		void resize(int32_t size);

	public:
		// 发送数据包不需要根据 m_size 截断，直接完整发送，反正其他端接收的时候也会因为数据包内存缓存也有空余浪费
		const uint8_t* getRawData() const;
		// 数据包大小
		int32_t getSize() const;
		int32_t getMaxSize() const;
		// 将数据拷贝到数据包的内存
		void setRawData(const uint8_t* data, const int32_t size);
		// 将数据拷贝到数据包的内存
		void setData(NetDataWriter* writer);

		// reader读取数据后回到对象池，但是依旧共享数据内存，需尽快处理
		void GetData(NetDataReader* reader);


	private:
		// 总数据，包含冗余未使用的空间
		uint8_t* RawData;
		// 当前占用的大小
		int32_t m_size;
		// 最多容量
		int32_t MaxSize;
	};
}