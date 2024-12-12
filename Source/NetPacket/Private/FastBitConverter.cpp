#include "nppch.h"
#include "FastBitConverter.h"

namespace NetPacket {

	// 获取指定类型的字节表示
	template <typename T>
	void FastBitConverter::GetBytes(uint8_t* bytes, int startIndex, T value) {
		static_assert(std::is_trivially_copyable<T>::value, "T must be a trivially copyable type");
		size_t size = sizeof(T);
		if (startIndex + size > 255) {
			throw std::out_of_range("Index is out of range.");
		}
		std::memcpy(&bytes[startIndex], &value, size);
	}

	// 针对不同类型的 GetBytes 重载

	void FastBitConverter::GetBytes(uint8_t* bytes, int startIndex, double value) {
		uint64_t temp = *reinterpret_cast<uint64_t*>(&value);
		WriteLittleEndian(bytes, startIndex, temp);
	}

	void FastBitConverter::GetBytes(uint8_t* bytes, int startIndex, float value) {
		int temp = *reinterpret_cast<int*>(&value);
		WriteLittleEndian(bytes, startIndex, temp);
	}

	void FastBitConverter::GetBytes(uint8_t* bytes, int startIndex, short value) {
		WriteLittleEndian(bytes, startIndex, value);
	}

	void FastBitConverter::GetBytes(uint8_t* bytes, int startIndex, unsigned short value) {
		WriteLittleEndian(bytes, startIndex, static_cast<short>(value));
	}

	void FastBitConverter::GetBytes(uint8_t* bytes, int startIndex, int value) {
		WriteLittleEndian(bytes, startIndex, value);
	}

	void FastBitConverter::GetBytes(uint8_t* bytes, int startIndex, unsigned int value) {
		WriteLittleEndian(bytes, startIndex, static_cast<int>(value));
	}

	void FastBitConverter::GetBytes(uint8_t* bytes, int startIndex, long value) {
		WriteLittleEndian(bytes, startIndex, static_cast<uint64_t>(value));
	}

	void FastBitConverter::GetBytes(uint8_t* bytes, int startIndex, unsigned long long value) {
		WriteLittleEndian(bytes, startIndex, value);
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

} // namespace NetPacket
