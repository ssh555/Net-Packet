#pragma once

namespace NetPacket {

	// 快速Bit转换器
	class NP_API FastBitConverter {
	public:
		// 获取指定类型的字节表示
		template <typename T>
		static void Put(uint8_t* bytes, int startIndex, T value);

		// 转换函数，用于不同类型的数据（ulong, double, int, float 等）
		static void Put(uint8_t* bytes, int startIndex, double value);
		static void Put(uint8_t* bytes, int startIndex, float value);
		static void Put(uint8_t* bytes, int startIndex, short value);
		static void Put(uint8_t* bytes, int startIndex, unsigned short value);
		static void Put(uint8_t* bytes, int startIndex, int value);
		static void Put(uint8_t* bytes, int startIndex, unsigned int value);
		static void Put(uint8_t* bytes, int startIndex, long long value);
		static void Put(uint8_t* bytes, int startIndex, unsigned long long value);


		// 从字节数组读取值并赋值给变量
		template <typename T>
		static void Get(const uint8_t* bytes, int startIndex, T& value);

		// 针对不同类型的 Get 重载
		static void Get(const uint8_t* bytes, int startIndex, double& value);
		static void Get(const uint8_t* bytes, int startIndex, float& value);
		static void Get(const uint8_t* bytes, int startIndex, short& value);
		static void Get(const uint8_t* bytes, int startIndex, unsigned short& value);
		static void Get(const uint8_t* bytes, int startIndex, int& value);
		static void Get(const uint8_t* bytes, int startIndex, unsigned int& value);
		static void Get(const uint8_t* bytes, int startIndex, long long& value);
		static void Get(const uint8_t* bytes, int startIndex, unsigned long long& value);



	private:
		// 用于将数据转换为字节表示的小端格式
		static void WriteLittleEndian(uint8_t* buffer, int offset, uint64_t data);
		static void WriteLittleEndian(uint8_t* buffer, int offset, int data);
		static void WriteLittleEndian(uint8_t* buffer, int offset, short data);

		// 从小端格式字节数组读取 uint64_t 类型的数据
		static uint64_t ReadLittleEndian64(const uint8_t* buffer, int offset);

		// 从小端格式字节数组读取 int 类型的数据
		static int ReadLittleEndian32(const uint8_t* buffer, int offset);

		// 从小端格式字节数组读取 short 类型的数据
		static short ReadLittleEndian16(const uint8_t* buffer, int offset);

	};

} // namespace NetPacket
