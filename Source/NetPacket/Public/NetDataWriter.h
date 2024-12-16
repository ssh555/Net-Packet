#pragma once
#include <string>
#include "INetSerializable.h"
#include "FastBitConverter.h"

#ifdef NP_UE_SUPPORT
#include "CoreMinimal.h"
#endif

namespace NetPacket {

	// ���� NetDataWriter ��
	class NP_API NetDataWriter
	{
	private:
		int32_t _position;  // ��ǰд��λ��
		bool _autoResize;  // �Ƿ��Զ���������
		uint8_t* _data;  // �洢���л�������
		int32_t _dataSize;           // ���ݴ�С

		void resize(int32_t size);

	public:
		static constexpr size_t InitialSize = 64;  // ��ʼ����
		static NetDataWriter* FromBytes(const uint8_t* bytes, int32_t size, bool copy);
		static NetDataWriter* FromBytes(const uint8_t* bytes, int32_t offset, int32_t length);
		static NetDataWriter* FromString(const std::string& value);

	public:
		// ���캯��
		NetDataWriter(bool autoResize = true, int32_t initialSize = InitialSize);
		~NetDataWriter();


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

		// ����ֱ��memcpy
		template <typename T>
		void PutArray(T* value, unsigned short length);

		// ����λ��
		int32_t SetPosition(int32_t position);

#ifdef NP_UE_SUPPORT
		void Put(const FString& value);
		void Put(const FName& value);
		void Put(const FText& value);
		void Put(const FVector& value);
		void Put(const FQuat& value);
		void Put(const FColor& value);
		void Put(const FIntPoint& value);
		void Put(const FVector2D& value);
		void Put(const FRotator& value);
		void Put(const FDateTime& value);
		void Put(const FTimespan& value);
		void Put(const FBox& value);
		void Put(const FMatrix& value);
		void Put(const FTransform& value);
		void Put(const FLinearColor& value);

		// ���л�TArray
		template <typename T>
		void PutArray(const TArray<T>& value);
		void PutArray(const TArray<FString>& value);
		void PutArray(const TArray<FName>& value);
		void PutArray(const TArray<FText>& value);
		void PutArray(const TArray<int64>& value);
		void PutArray(const TArray<int32>& value);
		void PutArray(const TArray<uint8>& value);
		void PutArray(const TArray<FVector>& value);
		void PutArray(const TArray<FQuat>& value);
		void PutArray(const TArray<FColor>& value);
		void PutArray(const TArray<FIntPoint>& value);
		void PutArray(const TArray<FVector2D>& value);
		void PutArray(const TArray<FRotator>& value);
		void PutArray(const TArray<FDateTime>& value);
		void PutArray(const TArray<FTimespan>& value);
		void PutArray(const TArray<FBox>& value);
		void PutArray(const TArray<FMatrix>& value);
		void PutArray(const TArray<FTransform>& value);
		void PutArray(const TArray<FLinearColor>& value);

#endif
	};

	template <typename T>
	void NetPacket::NetDataWriter::PutArray(T* value, unsigned short length)
	{
		int32_t size = sizeof(T) * length;

		Put(length);
		if (_autoResize)
			ResizeIfNeed(_position + size);
		memcpy((void*)value, _data + _position, size);
		_position += size;
	}
#ifdef NP_UE_SUPPORT

	template <typename T>
	void NetPacket::NetDataWriter::PutArray(const TArray<T>& value)
	{
		// ��ȡTArray�ĳ���
		auto length = value.Num();
		int32_t size = length * sizeof(T);

		Put(length);

		if (_autoResize)
			ResizeIfNeed(_position + size);
		// ʹ��FMemory::Memcpy�����ڴ濽��
		FMemory::Memcpy(_data + _position, value.GetData(), size);

		// ���µ�ǰд��λ��
		_position += size;
	}
#endif
}