#pragma once
#include <string>
#include "INetSerializable.h"


namespace NetPacket {

	// ���� UNetDataWriter ��
	class NP_API UNetDataWriter
	{
	private:
		uint8_t* _data;  // �洢���л�������
		int32_t _dataSize;           // ���ݴ�С
		void resize(int32_t size);

		int32_t _position;  // ��ǰд��λ��
		bool _autoResize;  // �Ƿ��Զ���������

	public:
		static constexpr size_t InitialSize = 64;  // ��ʼ����
		static UNetDataWriter FromBytes(uint8_t* bytes, int32_t size, bool copy);
		static UNetDataWriter FromBytes(uint8_t* bytes, int32_t offset, int32_t length);
		static UNetDataWriter FromString(std::string value);
		static UNetDataWriter FromString(const std::string& value);

	public:
		// ���캯��
		UNetDataWriter(bool autoResize = true, int32_t initialSize = InitialSize);


		// ��ȡ����
		int32_t Capacity() const;

		// ��ȡ����
		const uint8_t* Data() const;

		// ��ȡ��ǰ���ݳ���
		uint8_t Length() const;

		// ȷ�����ݴ�С�㹻
		void ResizeIfNeed(int32_t newSize);

		// ȷ����չ����
		void EnsureFit(int32_t additionalSize);

		// �������ݺ�λ��
		void Reset(int32_t size = 0);

		// ��������
		uint8_t* CopyData() const;

		// д�����ݷ���
		void Put(float value);
		void Put(char value);
		void Put(std::byte value);
		void Put(double value);
		void Put(bool value);
		void Put(int64_t value);
		void Put(uint64_t value);
		void Put(int32_t value);
		void Put(uint32_t value);
		void Put(int16_t value);
		void Put(uint16_t value);
		void Put(int8_t value);
		void Put(uint8_t value);
		void Put(const std::string& value);
		void Put(const uint8_t* data, const int size);
		void Put(const uint8_t* data, int32_t offset, int32_t length);
		template <typename T>
		typename std::enable_if<std::is_class<T>::value&& std::is_base_of<INetSerializable, T>::value, T>::type
			Put(T value);
		template <typename T>
		void PutArray(T* value, unsigned short length);
		void PutArray(const std::string* value, unsigned short length);
		template <typename T>
		typename std::enable_if<std::is_class<T>::value&& std::is_base_of<INetSerializable, T>::value, T>::type
			PutArray(T* value, unsigned short length);

		// ����λ��
		int32_t SetPosition(int32_t position);


	};

	template <typename T>
	typename std::enable_if<std::is_class<T>::value&& std::is_base_of<INetSerializable, T>::value, T>::type
		NetPacket::UNetDataWriter::PutArray(T* value, unsigned short length)
	{
		Put(length);
		for (int i = 0; i < length; i++)
			value[i].Serialize(this);
	}

	template <typename T>
	void NetPacket::UNetDataWriter::PutArray(T* value, unsigned short length)
	{
		int32_t size = sizeof(T) * length;
		if (_autoResize)
			ResizeIfNeed(_position + size + 2);
		FastBitConverter::GetBytes(_data, _position, length);
		if (value != nullptr)
		{
			delete[] value;
		}
		value = new T[length];
		memcpy(value, _data + _position, size);
		_position += size + 2;
	}

	template <typename T>
	typename std::enable_if<std::is_class<T>::value&& std::is_base_of<INetSerializable, T>::value, T>::type
		NetPacket::UNetDataWriter::Put(T value)
	{
		value.Serialize(this);
	}

}