#pragma once
#include <mutex>

namespace NetPacket
{
	class NetPackage;

	class NetPacketPool
	{
	public:
		static const int32_t PacketPoolSize = 1000;
		static const int32_t InitPoolSize = 30;

		NetPacketPool();
		~NetPacketPool();

		// 可用数量
		int32_t PoolCount() const;

		// 包含header
		// bWithHeader = false -> 自动添加header
		// = true -> data自带header
		NetPackage* GetPacket(const uint8_t* data, int32_t start, int32_t length, bool bWithHeader);
		NetPackage* GetPacket(int32_t size = 0);

		void Recycle(NetPackage* packet);

	private:
		NetPackage* InternalGetPacket(int32_t size);

		NetPackage* _poolHead;
		NetPackage* _poolEnd;

		int32_t _poolCount;

		mutable std::mutex _poolLock;
	};
}

