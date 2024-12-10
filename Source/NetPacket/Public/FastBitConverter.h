#pragma once

namespace NetPacket {

	// 快速Bit转换器
	class 
#if !NP_UE_SUPPORT
		NP_API
#endif
		FastBitConverter {
	public:
		// 获取指定类型的字节表示
		template <typename T>
		static void GetBytes(uint8_t* bytes, int startIndex, T value);

		// 转换函数，用于不同类型的数据（ulong, double, int, float 等）
		static void GetBytes(uint8_t* bytes, int startIndex, double value);
		static void GetBytes(uint8_t* bytes, int startIndex, float value);
		static void GetBytes(uint8_t* bytes, int startIndex, short value);
		static void GetBytes(uint8_t* bytes, int startIndex, unsigned short value);
		static void GetBytes(uint8_t* bytes, int startIndex, int value);
		static void GetBytes(uint8_t* bytes, int startIndex, unsigned int value);
		static void GetBytes(uint8_t* bytes, int startIndex, long value);
		static void GetBytes(uint8_t* bytes, int startIndex, unsigned long long value);

	private:
		// 用于将数据转换为字节表示的小端格式
		static void WriteLittleEndian(uint8_t* buffer, int offset, uint64_t data);
		static void WriteLittleEndian(uint8_t* buffer, int offset, int data);
		static void WriteLittleEndian(uint8_t* buffer, int offset, short data);
	};

} // namespace NetPacket
