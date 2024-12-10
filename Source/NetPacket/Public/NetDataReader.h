#pragma once

#include <string>
#include "INetSerializable.h"

namespace NetPacket
{
	class NetDataWriter;
	INTERFACE INetSerializable;

	class NP_API NetDataReader
	{
	public:
		// 构造函数和析构函数
		NetDataReader();
		NetDataReader(NetDataWriter writer);
		NetDataReader(uint8_t* source, int32_t size);
		NetDataReader(uint8_t* source, int32_t offset, int32_t maxSize);
		~NetDataReader();



		// 获取字节数据
		template <typename T>
		typename std::enable_if<std::is_class<T>::value&& std::is_base_of<INetSerializable, T>::value, T>::type
			GetStruct();

		uint8_t GetByte();

		int8_t GetSByte();

		bool GetBool();

		int16_t GetShort();

		uint16_t GetUShort();

		int32_t GetInt();

		uint32_t GetUInt();

		int64_t GetLong();

		uint64_t GetULong();

		float GetFloat();

		double GetDouble();

		std::string GetString();

		uint8_t* GetBytesWithLength();

		// 获取预读取的 ushort 数据
		uint16_t PeekUShort();

		template<typename T>
		T* GetArray();
		template <typename T>
		typename std::enable_if<std::is_class<T>::value&& std::is_base_of<INetSerializable, T>::value, T>::type
			GetArray();
		std::string* GetStringArray();

		// 清空数据
		void Clear();

		const uint8_t* GetRawData();
		int32_t GetRawDataSize();
		int32_t GetPosition();
		bool EndOfData();
		// 获取当前可用的字节数
		int32_t AvailableBytes() const;
		void SkipBytes(int32_t count);
		void SetPosition(int32_t position);
		void SetSource(NetDataWriter& dataWriter);
		void SetSource(uint8_t* source, int32_t size);
		void SetSource(uint8_t* source, int32_t offset, int32_t maxSize);

		uint8_t* GetRemainingBytes();

	private:
		uint8_t* _data; // 数据存储
		int32_t _position;           // 当前读取位置
		int32_t _dataSize;           // 数据大小
	};

	template<typename T>
	T* NetPacket::NetDataReader::GetArray()
	{
		int32_t size = sizeof(T);
		int32_t length = static_cast<int32_t>(PeekUShort());
		if (_position + length * size <= _dataSize) {
			T* value = new T[length];
			memcpy(value, _data + _position, length * size);
			_position += length * size;
			return value;
		}
		throw std::out_of_range("No enough data to get array");
	}

	template <typename T>
	typename std::enable_if<std::is_class<T>::value&& std::is_base_of<INetSerializable, T>::value, T>::type
		NetPacket::NetDataReader::GetArray()
	{
		int32_t size = sizeof(T);
		int32_t length = static_cast<int32_t>(PeekUShort());
		if (_position + length * size <= _dataSize) {
			T* value = new T[length];
			value->Deserialize(this);
			_position += length * size;
			return value;
		}
		throw std::out_of_range("No enough data to get array");
	}


	template <typename T>
	typename std::enable_if<std::is_class<T>::value&& std::is_base_of<INetSerializable, T>::value, T>::type
		NetPacket::NetDataReader::GetStruct()
	{
		T result;
		result.Deserialize(this);
		return result;
	}

}

