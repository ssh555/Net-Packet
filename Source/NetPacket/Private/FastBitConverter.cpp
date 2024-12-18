#include "nppch.h"
#include "FastBitConverter.h"

namespace NetPacket
{
	// ��ȡָ�����͵��ֽڱ�ʾ
	template <typename T>
	void FastBitConverter::Put(uint8_t* bytes, int startIndex, T value) {
		static_assert(std::is_trivially_copyable<T>::value, "T must be a trivially copyable type");
		size_t size = sizeof(T);
		if (startIndex + size > 255) {
			throw std::out_of_range("Index is out of range.");
		}
		std::memcpy(&bytes[startIndex], &value, size);
	}

	// ��Բ�ͬ���͵� Put ����

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


	// һ��ģ�庯�������ֽ������ȡֵ����ֵ������
	template <typename T>
	void FastBitConverter::Get(const uint8_t* bytes, int startIndex, T& value) {
		static_assert(std::is_trivially_copyable<T>::value, "T must be a trivially copyable type");
		size_t size = sizeof(T);
		if (startIndex + size > 255) {
			throw std::out_of_range("Index is out of range.");
		}
		std::memcpy(&value, &bytes[startIndex], size);
	}

	// ��� double ���͵����أ����ֽ������ȡС�˸�ʽ���ݲ�ת��Ϊ double
	void FastBitConverter::Get(const uint8_t* bytes, int startIndex, double& value) {
		uint64_t temp = ReadLittleEndian64(bytes, startIndex);
		value = *reinterpret_cast<double*>(&temp);
	}

	// ��� float ���͵����أ����ֽ������ȡС�˸�ʽ���ݲ�ת��Ϊ float
	void FastBitConverter::Get(const uint8_t* bytes, int startIndex, float& value) {
		int temp = ReadLittleEndian32(bytes, startIndex);
		value = *reinterpret_cast<float*>(&temp);
	}

	// ��� short ���͵����أ����ֽ������ȡС�˸�ʽ����
	void FastBitConverter::Get(const uint8_t* bytes, int startIndex, short& value) {
		value = ReadLittleEndian16(bytes, startIndex);
	}

	// ��� unsigned short ���͵����أ����ֽ������ȡС�˸�ʽ���ݲ�ת��Ϊ unsigned short
	void FastBitConverter::Get(const uint8_t* bytes, int startIndex, unsigned short& value) {
		value = static_cast<unsigned short>(ReadLittleEndian16(bytes, startIndex));
	}

	// ��� int ���͵����أ����ֽ������ȡС�˸�ʽ����
	void FastBitConverter::Get(const uint8_t* bytes, int startIndex, int& value) {
		value = ReadLittleEndian32(bytes, startIndex);
	}

	// ��� unsigned int ���͵����أ����ֽ������ȡС�˸�ʽ���ݲ�ת��Ϊ unsigned int
	void FastBitConverter::Get(const uint8_t* bytes, int startIndex, unsigned int& value) {
		value = static_cast<unsigned int>(ReadLittleEndian32(bytes, startIndex));
	}

	// ��� long ���͵����أ����ֽ������ȡС�˸�ʽ���ݲ�ת��Ϊ long
	void FastBitConverter::Get(const uint8_t* bytes, int startIndex, long long& value) {
		value = static_cast<long long>(ReadLittleEndian64(bytes, startIndex));
	}

	// ��� unsigned long long ���͵����أ����ֽ������ȡС�˸�ʽ����
	void FastBitConverter::Get(const uint8_t* bytes, int startIndex, unsigned long long& value) {
		value = ReadLittleEndian64(bytes, startIndex);
	}



	// ������ת��Ϊ�ֽڱ�ʾ��С�˸�ʽ
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

	// ��С�˸�ʽ�ֽ������ȡ uint64_t ���͵�����
	uint64_t FastBitConverter::ReadLittleEndian64(const uint8_t* buffer, int offset) {
		uint64_t result = 0;
		for (int i = 0; i < 8; ++i) {
			result |= static_cast<uint64_t>(buffer[offset + i]) << (i * 8);
		}
		return result;
	}

	// ��С�˸�ʽ�ֽ������ȡ int ���͵�����
	int FastBitConverter::ReadLittleEndian32(const uint8_t* buffer, int offset) {
		int result = 0;
		for (int i = 0; i < 4; ++i) {
			result |= static_cast<int>(buffer[offset + i]) << (i * 8);
		}
		return result;
	}

	// ��С�˸�ʽ�ֽ������ȡ short ���͵�����
	short FastBitConverter::ReadLittleEndian16(const uint8_t* buffer, int offset) {
		return static_cast<short>(buffer[offset] | (buffer[offset + 1] << 8));
	}


} // namespace NetPacket
