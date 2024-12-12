#pragma once

#include <string>
#include "INetSerializable.h"

#if NP_UE_SUPPORT
#include "CoreMinimal.h"
#endif

namespace NetPacket
{
	class NetDataWriter;
	class INetSerializable;

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

		// 获取预读取的 ushort 数据
		// true: 获取数据并前进
		// false: 只获取数据，下一次调用还是同样的数据
		// Processor 使用时不能弹出
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

		// 清空数据
		void Clear(bool isDelete = true);

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

#if NP_UE_SUPPORT
		void Get(FString& value);
		void Get(FVector& value);
		void Get(FQuat& value);
		void Get(FColor& value);
		void Get(FIntPoint& value);
		void Get(FVector2D& value);
		void Get(FRotator& value);
		void Get(FDateTime& value);
		void Get(FTimespan& value);
		void Get(FBox& value);
		void Get(FMatrix& value);
		void Get(FTransform& value);
		void Get(FLinearColor& value);

		// 序列化TArray
		template <typename T>
		uint16_t GetArray(TArray<T>& value);
		uint16_t GetArray(TArray<FString>& value);
		uint16_t GetArray(TArray<FVector>& value);
		uint16_t GetArray(TArray<FQuat>& value);
		uint16_t GetArray(TArray<FColor>& value);
		uint16_t GetArray(TArray<FIntPoint>& value);
		uint16_t GetArray(TArray<FVector2D>& value);
		uint16_t GetArray(TArray<FRotator>& value);
		uint16_t GetArray(TArray<FDateTime>& value);
		uint16_t GetArray(TArray<FTimespan>& value);
		uint16_t GetArray(TArray<FBox>& value);
		uint16_t GetArray(TArray<FMatrix>& value);
		uint16_t GetArray(TArray<FTransform>& value);
		uint16_t GetArray(TArray<FLinearColor>& value);

#endif

	private:
		int32_t _position;           // 当前读取位置
		int32_t _dataSize;           // 数据大小
		uint8_t* _data; // 数据存储
	};

	template<typename T>
	uint16_t NetPacket::NetDataReader::GetArray(T* value)
	{
		int32_t size = sizeof(T);
		uint16_t length = PeekUShort();
		if (_position + (int32_t)length * size <= _dataSize) {
			memcpy(value, _data + _position, (int32_t)length * size);
			_position += length * size;
			return length;
		}
		throw std::out_of_range("No enough data to get array");
	}
#if NP_UE_SUPPORT

	template<typename T>
	uint16_t NetPacket::NetDataReader::GetArray(TArray<T>& value)
	{
		int32_t size = sizeof(T);
		uint16_t length = PeekUShort();
		if (_position + length * size <= _dataSize) {
			value.SetNumUninitialized(length);

			FMemory::Memcpy(value.GetData(), _data + _position, length * size);

			_position += length * size;
			return length;
		}

		throw std::out_of_range("Not enough data to get array");
	}
#endif
}

