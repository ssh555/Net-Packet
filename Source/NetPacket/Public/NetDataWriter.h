#pragma once
#include <string>
#include "INetSerializable.h"


// 放置于include最后
#if WITH_ENGINE
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include NP_GENERATE(NetDataWriter)
#endif

namespace NetPacket {

	// 定义 UNetDataWriter 类
	NP_UCLASS(NotBlueprintable, BlueprintType)
	class NP_API UNetDataWriter
#if WITH_ENGINE
		: public UObject
#endif
	{
		NP_GENERATED_BODY()

	private:
		uint8_t* _data;  // 存储序列化的数据
		int32_t _dataSize;           // 数据大小
		void resize(int32_t size);

		int32_t _position;  // 当前写入位置
		bool _autoResize;  // 是否自动调整容量

	public:
		static constexpr size_t InitialSize = 64;  // 初始容量
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		static UNetDataWriter FromBytes(uint8_t* bytes, int32_t size, bool copy);
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		static UNetDataWriter FromBytes(uint8_t* bytes, int32_t offset, int32_t length);
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		static UNetDataWriter FromString(std::string value);
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		static UNetDataWriter FromString(const std::string& value);

	public:
		// 构造函数
		UNetDataWriter(bool autoResize = true, int32_t initialSize = InitialSize);


		// 获取容量
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		int32_t Capacity() const;

		// 获取数据
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		const uint8_t* Data() const;

		// 获取当前数据长度
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		uint8_t Length() const;

		// 确保数据大小足够
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		void ResizeIfNeed(int32_t newSize);

		// 确保扩展容量
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		void EnsureFit(int32_t additionalSize);

		// 重置数据和位置
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		void Reset(int32_t size = 0);

		// 拷贝数据
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		uint8_t* CopyData() const;

		// 写入数据方法
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		void Put(float value);
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		void Put(char value);
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		void Put(std::byte value);
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		void Put(double value);
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		void Put(bool value);
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		void Put(int64_t value);
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		void Put(uint64_t value);
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		void Put(int32_t value);
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		void Put(uint32_t value);
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		void Put(int16_t value);
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		void Put(uint16_t value);
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		void Put(int8_t value);
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		void Put(uint8_t value);
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		void Put(const std::string& value);
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		void Put(const uint8_t* data, const int size);
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		void Put(const uint8_t* data, int32_t offset, int32_t length);
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		template <typename T>
		typename std::enable_if<std::is_class<T>::value&& std::is_base_of<INetSerializable, T>::value, T>::type
		Put(T value);
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		template <typename T>
		void PutArray(T* value, unsigned short length);
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		void PutArray(const std::string* value, unsigned short length);
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
		template <typename T>
		typename std::enable_if<std::is_class<T>::value&& std::is_base_of<INetSerializable, T>::value, T>::type
		PutArray(T* value, unsigned short length);

		// 重置位置
		NP_UFUNCTION(BlueprintCallable, Category = "NetPacket")
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