#pragma once

#include <string>
#include "INetSerializable.h"

// 放置于include最后
#if NP_UE_SUPPORT
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include NP_GENERATE(NetDataReader)
#endif

namespace NetPacket
{
	class UNetDataWriter;
	INTERFACE INetSerializable;

	// 继承 UObject 以便支持 Unreal 的反射和序列化系统
	NP_UCLASS(NotBlueprintable, BlueprintType)
	class NP_API UNetDataReader
#if NP_UE_SUPPORT
		: public UObject
#endif
	{

		NP_GENERATED_BODY()

	public:
		// 构造函数和析构函数
		UNetDataReader();
		UNetDataReader(UNetDataWriter writer);
		UNetDataReader(uint8_t* source, int32_t size);
		UNetDataReader(uint8_t* source, int32_t offset, int32_t maxSize);
		~UNetDataReader();



		// 获取字节数据
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		template <typename T>
		typename std::enable_if<std::is_class<T>::value&& std::is_base_of<INetSerializable, T>::value, T>::type
		GetStruct();

		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		uint8_t GetByte();

		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		int8_t GetSByte();

		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		bool GetBool();

		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		int16_t GetShort();

		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		uint16_t GetUShort();

		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		int32_t GetInt();

		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		uint32_t GetUInt();

		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		int64_t GetLong();

		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		uint64_t GetULong();

		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		float GetFloat();

		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		double GetDouble();

		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		std::string GetString();

		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		uint8_t* GetBytesWithLength();

		// 获取预读取的 ushort 数据
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		uint16_t PeekUShort();

		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		template<typename T>
		T* GetArray();
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
			template <typename T>
		typename std::enable_if<std::is_class<T>::value&& std::is_base_of<INetSerializable, T>::value, T>::type
		GetArray();
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		std::string* GetStringArray();

		// 清空数据
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		void Clear();

		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		const uint8_t* GetRawData();
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		int32_t GetRawDataSize();
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		int32_t GetPosition();
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		bool EndOfData();
		// 获取当前可用的字节数
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		int32_t AvailableBytes() const;
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		void SkipBytes(int32_t count);
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		void SetPosition(int32_t position);
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		void SetSource(UNetDataWriter& dataWriter);
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		void SetSource(uint8_t* source, int32_t size);
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		void SetSource(uint8_t* source, int32_t offset, int32_t maxSize);

		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		uint8_t* GetRemainingBytes();

	private:
		uint8_t* _data; // 数据存储
		int32_t _position;           // 当前读取位置
		int32_t _dataSize;           // 数据大小
	};

	template<typename T>
	T* NetPacket::UNetDataReader::GetArray()
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
	NetPacket::UNetDataReader::GetArray()
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
	typename std::enable_if<std::is_class<T>::value && std::is_base_of<INetSerializable, T>::value, T>::type
	NetPacket::UNetDataReader::GetStruct()
	{
		T result;
		result.Deserialize(this);
		return result;
	}

}

