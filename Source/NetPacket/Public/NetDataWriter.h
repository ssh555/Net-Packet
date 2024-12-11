#pragma once
#include <string>
#include "INetSerializable.h"
#include "FastBitConverter.h"


namespace NetPacket {

	// 定义 NetDataWriter 类
	class NP_API NetDataWriter
	{
	private:
		uint8_t* _data;  // 存储序列化的数据
		int32_t _dataSize;           // 数据大小
		void resize(int32_t size);

		int32_t _position;  // 当前写入位置
		bool _autoResize;  // 是否自动调整容量

	public:
		static constexpr size_t InitialSize = 64;  // 初始容量
		static NetDataWriter FromBytes(uint8_t* bytes, int32_t size, bool copy);
		static NetDataWriter FromBytes(uint8_t* bytes, int32_t offset, int32_t length);
		static NetDataWriter FromString(std::string value);
		static NetDataWriter FromString(const std::string& value);

	public:
		// 构造函数
		NetDataWriter(bool autoResize = true, int32_t initialSize = InitialSize);
		~NetDataWriter();


		// 获取容量
		int32_t Capacity() const;

		// 获取数据
		const uint8_t* Data() const;

		// 获取当前数据长度
		uint8_t Length() const;

		// 确保数据大小足够
		void ResizeIfNeed(int32_t newSize);

		// 确保扩展容量
		void EnsureFit(int32_t additionalSize);

		// 重置数据和位置
		void Reset(int32_t size = 0);

		// 拷贝数据
		uint8_t* CopyData() const;

		// 写入数据方法
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
		void Put(const INetSerializable& value);
		void Put(const uint8_t* data, const int size);
		void Put(const uint8_t* data, int32_t offset, int32_t length);

		void PutArray(const std::string* value, unsigned short length);
		void PutArray(INetSerializable* value, unsigned short length);
		void PutArray(float* value, unsigned short length);
		void PutArray(char* value, unsigned short length);
		void PutArray(std::byte* value, unsigned short length);
		void PutArray(double* value, unsigned short length);
		void PutArray(bool* value, unsigned short length);
		void PutArray(int64_t* value, unsigned short length);
		void PutArray(uint64_t* value, unsigned short length);
		void PutArray(int32_t* value, unsigned short length);
		void PutArray(uint32_t* value, unsigned short length);
		void PutArray(int16_t* value, unsigned short length);
		void PutArray(uint16_t* value, unsigned short length);
		void PutArray(int8_t* value, unsigned short length);
		void PutArray(uint8_t* value, unsigned short length);

		// 数据直接memcpy
		template <typename T>
		void PutArray(T* value, unsigned short length);

		// 重置位置
		int32_t SetPosition(int32_t position);
	};

	template <typename T>
	void NetPacket::NetDataWriter::PutArray(T* value, unsigned short length)
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
}