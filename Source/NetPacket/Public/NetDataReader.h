#pragma once

#include <string>
#include "INetSerializable.h"

namespace NetPacket
{
	class NetDataWriter;
	class INetSerializable;

	class NP_API NetDataReader
	{
	public:
		// ���캯������������
		NetDataReader();
		NetDataReader(NetDataWriter writer);
		NetDataReader(uint8_t* source, int32_t size);
		NetDataReader(uint8_t* source, int32_t offset, int32_t maxSize);
		~NetDataReader();



		// ��ȡ�ֽ�����
		void Get(uint8_t& value);
		void Get(int8_t& value);
		void Get(bool& value);
		void Get(int16_t& value);
		void Get(uint16_t& value);
		void Get(int32_t& value);
		void Get(uint32_t& value);
		void Get(int64_t& value);
		void Get(uint64_t& value);
		void Get(float& value);
		void Get(double& value);
		void Get(std::string& value);
		void Get(INetSerializable& value);
		void Get(char& value);
		void Get(std::byte& value);

		// ��ȡԤ��ȡ�� ushort ����
		// true: ��ȡ���ݲ�ǰ��
		// false: ֻ��ȡ���ݣ���һ�ε��û���ͬ��������
		// Processor ʹ��ʱ���ܵ���
		uint16_t PeekUShort(bool isPop = true);

		template<typename T>
		uint16_t GetArray(T* value);
		uint16_t GetArray(INetSerializable* value);
		uint16_t GetArray(std::string* data);
		uint16_t GetArray(uint8_t* data);
		uint16_t GetArray(int8_t* data);
		uint16_t GetArray(bool* data);
		uint16_t GetArray(int16_t* data);
		uint16_t GetArray(uint16_t* data);
		uint16_t GetArray(int32_t* data);
		uint16_t GetArray(uint32_t* data);
		uint16_t GetArray(int64_t* data);
		uint16_t GetArray(uint64_t* data);
		uint16_t GetArray(float* data);
		uint16_t GetArray(double* data);
		uint16_t GetArray(char* data);
		uint16_t GetArray(std::byte* data);

		// �������
		void Clear(bool isDelete = true);

		const uint8_t* GetRawData();
		int32_t GetRawDataSize();
		int32_t GetPosition();
		bool EndOfData();
		// ��ȡ��ǰ���õ��ֽ���
		int32_t AvailableBytes() const;
		void SkipBytes(int32_t count);
		void SetPosition(int32_t position);
		void SetSource(NetDataWriter& dataWriter);
		void SetSource(uint8_t* source, int32_t size);
		void SetSource(uint8_t* source, int32_t offset, int32_t maxSize);

		uint8_t* GetRemainingBytes();

	private:
		uint8_t* _data; // ���ݴ洢
		int32_t _position;           // ��ǰ��ȡλ��
		int32_t _dataSize;           // ���ݴ�С
	};

	template<typename T>
	uint16_t NetPacket::NetDataReader::GetArray(T* value)
	{
		int32_t size = sizeof(T);
		uint16_t length = PeekUShort();
		if (_position + (int32_t)length * size <= _dataSize) {
			T* value = new T[length];
			memcpy(value, _data + _position, (int32_t)length * size);
			_position += length * size;
			return length;
		}
		throw std::out_of_range("No enough data to get array");
	}
}

