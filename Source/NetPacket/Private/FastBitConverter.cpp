#include "nppch.h"
#include "FastBitConverter.h"

namespace NetPacket
{
	// 获取指定类型的字节表示
	template <typename T>
	void FastBitConverter::Put(uint8_t* bytes, int startIndex, T value) {
		static_assert(std::is_trivially_copyable<T>::value, "T must be a trivially copyable type");
		size_t size = sizeof(T);
		if (startIndex + size > 255) {
			throw std::out_of_range("Index is out of range.");
		}
		std::memcpy(&bytes[startIndex], &value, size);
	}

	// 针对不同类型的 Put 重载

	void FastBitConverter::Put(uint8_t* bytes, int startIndex, double value) {
		uint64_t temp = *reinterpret_cast<uint64_t*>(&value);
		WriteLittleEndian(bytes, startIndex, temp);
	}

	void FastBitConverter::Put(uint8_t* bytes, int startIndex, float value) {
		int temp = *reinterpret_cast<int*>(&value);
		WriteLittleEndian(bytes, startIndex, temp);
	}

	void FastBitConverter::Put(uint8_t* bytes, int startIndex, short value) {
		WriteLittleEndian(bytes, startIndex, value);
	}

	void FastBitConverter::Put(uint8_t* bytes, int startIndex, unsigned short value) {
		WriteLittleEndian(bytes, startIndex, static_cast<short>(value));
	}

	void FastBitConverter::Put(uint8_t* bytes, int startIndex, int value) {
		WriteLittleEndian(bytes, startIndex, value);
	}

	void FastBitConverter::Put(uint8_t* bytes, int startIndex, unsigned int value) {
		WriteLittleEndian(bytes, startIndex, static_cast<int>(value));
	}

	void FastBitConverter::Put(uint8_t* bytes, int startIndex, long long value) {
		WriteLittleEndian(bytes, startIndex, static_cast<uint64_t>(value));
	}

	void FastBitConverter::Put(uint8_t* bytes, int startIndex, unsigned long long value) {
		WriteLittleEndian(bytes, startIndex, value);
	}


	// 一般模板函数：从字节数组读取值并赋值给变量
	template <typename T>
	void FastBitConverter::Get(const uint8_t* bytes, int startIndex, T& value) {
		static_assert(std::is_trivially_copyable<T>::value, "T must be a trivially copyable type");
		size_t size = sizeof(T);
		if (startIndex + size > 255) {
			throw std::out_of_range("Index is out of range.");
		}
		std::memcpy(&value, &bytes[startIndex], size);
	}

	// 针对 double 类型的重载：从字节数组读取小端格式数据并转换为 double
	void FastBitConverter::Get(const uint8_t* bytes, int startIndex, double& value) {
		uint64_t temp = ReadLittleEndian64(bytes, startIndex);
		value = *reinterpret_cast<double*>(&temp);
	}

	// 针对 float 类型的重载：从字节数组读取小端格式数据并转换为 float
	void FastBitConverter::Get(const uint8_t* bytes, int startIndex, float& value) {
		int temp = ReadLittleEndian32(bytes, startIndex);
		value = *reinterpret_cast<float*>(&temp);
	}

	// 针对 short 类型的重载：从字节数组读取小端格式数据
	void FastBitConverter::Get(const uint8_t* bytes, int startIndex, short& value) {
		value = ReadLittleEndian16(bytes, startIndex);
	}

	// 针对 unsigned short 类型的重载：从字节数组读取小端格式数据并转换为 unsigned short
	void FastBitConverter::Get(const uint8_t* bytes, int startIndex, unsigned short& value) {
		value = static_cast<unsigned short>(ReadLittleEndian16(bytes, startIndex));
	}

	// 针对 int 类型的重载：从字节数组读取小端格式数据
	void FastBitConverter::Get(const uint8_t* bytes, int startIndex, int& value) {
		value = ReadLittleEndian32(bytes, startIndex);
	}

	// 针对 unsigned int 类型的重载：从字节数组读取小端格式数据并转换为 unsigned int
	void FastBitConverter::Get(const uint8_t* bytes, int startIndex, unsigned int& value) {
		value = static_cast<unsigned int>(ReadLittleEndian32(bytes, startIndex));
	}

	// 针对 long 类型的重载：从字节数组读取小端格式数据并转换为 long
	void FastBitConverter::Get(const uint8_t* bytes, int startIndex, long long& value) {
		value = static_cast<long long>(ReadLittleEndian64(bytes, startIndex));
	}

	// 针对 unsigned long long 类型的重载：从字节数组读取小端格式数据
	void FastBitConverter::Get(const uint8_t* bytes, int startIndex, unsigned long long& value) {
		value = ReadLittleEndian64(bytes, startIndex);
	}



	// 将数据转换为字节表示的小端格式
	void FastBitConverter::WriteLittleEndian(uint8_t* buffer, int offset, uint64_t data) {
		for (int i = 0; i < 8; ++i) {
			buffer[offset + i] = static_cast<uint8_t>(data >> (i * 8));
		}
	}

	void FastBitConverter::WriteLittleEndian(uint8_t* buffer, int offset, int data) {
		for (int i = 0; i < 4; ++i) {
			buffer[offset + i] = static_cast<uint8_t>(data >> (i * 8));
		}
	}

	void FastBitConverter::WriteLittleEndian(uint8_t* buffer, int offset, short data) {
		buffer[offset] = static_cast<uint8_t>(data);
		buffer[offset + 1] = static_cast<uint8_t>(data >> 8);
	}

	// 从小端格式字节数组读取 uint64_t 类型的数据
	uint64_t FastBitConverter::ReadLittleEndian64(const uint8_t* buffer, int offset) {
		uint64_t result = 0;
		for (int i = 0; i < 8; ++i) {
			result |= static_cast<uint64_t>(buffer[offset + i]) << (i * 8);
		}
		return result;
	}

	// 从小端格式字节数组读取 int 类型的数据
	int FastBitConverter::ReadLittleEndian32(const uint8_t* buffer, int offset) {
		int result = 0;
		for (int i = 0; i < 4; ++i) {
			result |= static_cast<int>(buffer[offset + i]) << (i * 8);
		}
		return result;
	}

	// 从小端格式字节数组读取 short 类型的数据
	short FastBitConverter::ReadLittleEndian16(const uint8_t* buffer, int offset) {
		return static_cast<short>(buffer[offset] | (buffer[offset + 1] << 8));
	}


} // namespace NetPacket
