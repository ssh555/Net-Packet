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

	class NP_API NetPackage {
		// 添加对象池的友元
		friend class NetPacketPool;
	public:
		constexpr static int32_t MaxPacketSize = 2048;
		constexpr static int32_t HeaderSize = 6;

	private:
		// 设置数据包大小
		NetPackage(uint32_t maxSize = 1024);
		~NetPackage();

		void resize(int32_t size);

	public:
		// 发送数据包不需要根据 m_size 截断，直接完整发送，反正其他端接收的时候也会因为数据包内存缓存也有空余浪费
		const uint8_t* getRawData() const;
		// 数据包大小
		int32_t getSize() const;
		int32_t getMaxSize() const;

		// 包含header
		// bWithHeader = false -> 自动添加header
		// = true -> data自带header
		void setRawData(const uint8_t* data, const int32_t size, bool bWithHeader);
		// 将数据拷贝到数据包的内存
		void setData(NetDataWriter* writer);

		// reader读取数据后回到对象池，但是依旧共享数据内存，需尽快处理 -> 不包含header
		void GetData(NetDataReader* reader);

		int16_t GetClientID() const;

		void SetClientID(int16_t cid);


	private:
		// 最多容量
		int32_t MaxSize;
		// 总数据，包含冗余未使用的空间
		uint8_t* RawData;
		// 当前占用的大小: 最大也比MaxSize小HeaderSize
		// 实际数据的大小，不包括Header
		int32_t m_size;
		NetPackage* Next;

	};
}