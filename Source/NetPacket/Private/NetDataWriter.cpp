#include "nppch.h"
#include "NetDataWriter.h"
#include "FastBitConverter.h"

constexpr size_t NetPacket::NetDataWriter::InitialSize;

NetPacket::NetDataWriter::NetDataWriter(bool autoResize /*= true*/, int32_t initialSize /*= InitialSize*/) : _position(0), _autoResize(autoResize), _data(new uint8_t[initialSize]), _dataSize(initialSize)
{

}

NetPacket::NetDataWriter::~NetDataWriter()
{
	delete[] _data;
}

int32_t NetPacket::NetDataWriter::Capacity() const
{
	return _dataSize;
}

const uint8_t* NetPacket::NetDataWriter::Data() const
{
	return _data;
}

int32_t NetPacket::NetDataWriter::Length() const
{
	return _position;
}

void NetPacket::NetDataWriter::ResizeIfNeed(int32_t newSize)
{
	if (_dataSize < newSize) {
		resize(std::max(newSize, _dataSize * 2));
	}
}

void NetPacket::NetDataWriter::EnsureFit(int32_t additionalSize)
{
	if (_dataSize < _position + additionalSize) {
		resize(std::max(_position + additionalSize, _dataSize * 2));
	}
}

void NetPacket::NetDataWriter::Reset(int32_t size /*= 0*/)
{
	ResizeIfNeed(size);
	_position = 0;
}

uint8_t* NetPacket::NetDataWriter::CopyData() const
{
	uint8_t* resultData = new uint8_t[_position];
	std::memcpy(resultData, _data, _position);
	return resultData;
}

int32_t NetPacket::NetDataWriter::SetPosition(int32_t position)
{
	int32_t prevPosition = _position;
	_position = position;
	return prevPosition;
}

void NetPacket::NetDataWriter::Put(float value)
{
	ResizeIfNeed(_position + sizeof(float));
	FastBitConverter::Put(_data, _position, value);
	_position += sizeof(float);
}

void NetPacket::NetDataWriter::Put(const INetSerializable& value)
{
	value.Serialize(*this);
}

void NetPacket::NetDataWriter::Put(const uint8_t* data, const int size)
{
	ResizeIfNeed(_position + size);
	std::memcpy(_data + _position, data, size);
	_position += size;
}

void NetPacket::NetDataWriter::Put(const uint8_t* data, int32_t offset, int32_t length)
{
	ResizeIfNeed(_position + length);
	std::memcpy(_data + _position, data + offset, length);
	_position += length;
}

void NetPacket::NetDataWriter::Put(const std::string& value)
{
	uint16_t size = static_cast<uint16_t>(value.size());
	Put(size);
	ResizeIfNeed(_position + size);
	std::memcpy(_data + _position, value.c_str(), size);
	_position += size;
}

void NetPacket::NetDataWriter::Put(uint8_t value)
{
	ResizeIfNeed(_position + sizeof(uint8_t));
	_data[_position] = value;
	_position += sizeof(uint8_t);
}

void NetPacket::NetDataWriter::Put(int8_t value)
{
	ResizeIfNeed(_position + sizeof(int8_t));
	_data[_position] = value;
	_position += sizeof(int8_t);
}

void NetPacket::NetDataWriter::Put(uint16_t value)
{
	ResizeIfNeed(_position + sizeof(uint16_t));
	FastBitConverter::Put(_data, _position, value);
	_position += sizeof(uint16_t);
}

void NetPacket::NetDataWriter::Put(int16_t value)
{
	ResizeIfNeed(_position + sizeof(int16_t));
	FastBitConverter::Put(_data, _position, value);
	_position += sizeof(int16_t);
}

void NetPacket::NetDataWriter::Put(uint32_t value)
{
	ResizeIfNeed(_position + sizeof(uint32_t));
	FastBitConverter::Put(_data, _position, value);
	_position += sizeof(uint32_t);
}

void NetPacket::NetDataWriter::Put(int32_t value)
{
	ResizeIfNeed(_position + sizeof(int32_t));
	FastBitConverter::Put(_data, _position, value);
	_position += sizeof(int32_t);
}

void NetPacket::NetDataWriter::Put(uint64_t value)
{
	ResizeIfNeed(_position + sizeof(uint64_t));
	FastBitConverter::Put(_data, _position, value);
	_position += sizeof(uint64_t);
}

void NetPacket::NetDataWriter::Put(int64_t value)
{
	ResizeIfNeed(_position + sizeof(int64_t));
	FastBitConverter::Put(_data, _position, value);
	_position += sizeof(int64_t);
}

void NetPacket::NetDataWriter::Put(double value)
{
	ResizeIfNeed(_position + sizeof(double));
	FastBitConverter::Put(_data, _position, value);
	_position += sizeof(double);
}

void NetPacket::NetDataWriter::Put(char value)
{
	ResizeIfNeed(_position + sizeof(char));
	std::memcpy(_data + _position, &value, sizeof(char));
	_position += sizeof(char);
}

void NetPacket::NetDataWriter::Put(std::byte value)
{
	ResizeIfNeed(_position + sizeof(std::byte));
	std::memcpy(_data + _position, &value, sizeof(std::byte));
	_position += sizeof(std::byte);
}

void NetPacket::NetDataWriter::Put(bool value)
{
	ResizeIfNeed(_position + sizeof(bool));
	std::memcpy(_data + _position, &value, sizeof(bool));
	_position += sizeof(bool);
}

void NetPacket::NetDataWriter::resize(int32_t size)
{
	if (size > _dataSize)
	{
		uint8_t* newData = new uint8_t[size];
		std::memcpy(newData, _data, _dataSize);
		delete[] _data;
		_data = newData;
		_dataSize = size;
	}
}


NetPacket::NetDataWriter* NetPacket::NetDataWriter::FromBytes(const uint8_t* bytes, int32_t size, bool copy)
{
	if (copy)
	{
		auto netDataWriter = new NetDataWriter(true, size);
		netDataWriter->Put(bytes, size);
		return netDataWriter;
	}
	NetDataWriter* netDataWriter = new NetDataWriter(true, 0);
	netDataWriter->_data = const_cast<uint8_t*>(bytes);
	netDataWriter->_dataSize = size;
	netDataWriter->_position = size;
	return netDataWriter;
}

NetPacket::NetDataWriter* NetPacket::NetDataWriter::FromBytes(const uint8_t* bytes, int32_t offset, int32_t length)
{
	NetDataWriter* netDataWriter = new NetDataWriter(true, length);
	netDataWriter->Put(bytes, offset, length);
	return netDataWriter;
}

NetPacket::NetDataWriter* NetPacket::NetDataWriter::FromString(const std::string& value)
{
	auto netDataWriter = new NetDataWriter();
	netDataWriter->Put(value);
	return netDataWriter;
}

void NetPacket::NetDataWriter::PutArray(const std::string* value, unsigned short length)
{
	Put(length);
	for (int i = 0; i < length; i++)
		Put(value[i]);
}

void NetPacket::NetDataWriter::PutArray(uint8_t* value, unsigned short length)
{
	PutArray<uint8_t>(value, length);
}

void NetPacket::NetDataWriter::PutArray(int8_t* value, unsigned short length)
{
	PutArray<int8_t>(value, length);
}

void NetPacket::NetDataWriter::PutArray(uint16_t* value, unsigned short length)
{
	PutArray<uint16_t>(value, length);
}

void NetPacket::NetDataWriter::PutArray(int16_t* value, unsigned short length)
{
	PutArray<int16_t>(value, length);
}

void NetPacket::NetDataWriter::PutArray(uint32_t* value, unsigned short length)
{
	PutArray<uint32_t>(value, length);
}

void NetPacket::NetDataWriter::PutArray(int32_t* value, unsigned short length)
{
	PutArray<int32_t>(value, length);
}

void NetPacket::NetDataWriter::PutArray(uint64_t* value, unsigned short length)
{
	PutArray<uint64_t>(value, length);
}

void NetPacket::NetDataWriter::PutArray(int64_t* value, unsigned short length)
{
	PutArray<int64_t>(value, length);
}

void NetPacket::NetDataWriter::PutArray(bool* value, unsigned short length)
{
	PutArray<bool>(value, length);
}

void NetPacket::NetDataWriter::PutArray(double* value, unsigned short length)
{
	PutArray<double>(value, length);
}

void NetPacket::NetDataWriter::PutArray(std::byte* value, unsigned short length)
{
	PutArray<std::byte>(value, length);
}

void NetPacket::NetDataWriter::PutArray(char* value, unsigned short length)
{
	PutArray<char>(value, length);
}

void NetPacket::NetDataWriter::PutArray(float* value, unsigned short length)
{
	PutArray<float>(value, length);
}

void NetPacket::NetDataWriter::PutArray(INetSerializable* value, unsigned short length)
{
	Put(length);
	for (int i = 0; i < length; i++)
		value[i].Serialize(*this);
}

#if NP_UE_SUPPORT
void NetPacket::NetDataWriter::Put(const FString& value)
{
	FTCHARToUTF8 utf8Str(*value);
	int16_t strLength = utf8Str.Length();
	Put((int16_t)(strLength + 1));

	ResizeIfNeed(_position + strLength);
	FMemory::Memcpy(_data + _position, utf8Str.Get(), strLength);
	_position += strLength;
	Put('\0');
}

void NetPacket::NetDataWriter::Put(const FName& value)
{
	FString str = value.ToString();
	Put(str);
}

void NetPacket::NetDataWriter::Put(const FText& value)
{
	// 处理 FText 类型的写入
	FString tempStr = value.ToString();  // 获取基础字符串
	Put(tempStr);
}

void NetPacket::NetDataWriter::Put(const FVector& value)
{
	Put(value.X);
	Put(value.Y);
	Put(value.Z);
}

void NetPacket::NetDataWriter::Put(const FLinearColor& value)
{
	Put(value.R);
	Put(value.G);
	Put(value.B);
	Put(value.A);
}

void NetPacket::NetDataWriter::Put(const FTransform& value)
{
	Put(value.GetLocation());
	Put(value.GetRotation());
	Put(value.GetScale3D());
}

void NetPacket::NetDataWriter::Put(const FMatrix& value)
{
	auto data = value.M;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			Put(data[i][j]);
		}
	}
}

void NetPacket::NetDataWriter::Put(const FBox& value)
{
	Put(value.Min);
	Put(value.Max);
}

void NetPacket::NetDataWriter::Put(const FTimespan& value)
{
	Put(value.GetTicks());
}

void NetPacket::NetDataWriter::Put(const FDateTime& value)
{
	Put(value.GetTicks());
}

void NetPacket::NetDataWriter::Put(const FRotator& value)
{
	Put(value.Pitch);
	Put(value.Yaw);
	Put(value.Roll);
}

void NetPacket::NetDataWriter::Put(const FVector2D& value)
{
	Put(value.X);
	Put(value.Y);
}

void NetPacket::NetDataWriter::Put(const FIntPoint& value)
{
	Put(value.X);
	Put(value.Y);
}

void NetPacket::NetDataWriter::Put(const FColor& value)
{
	Put(value.R);
	Put(value.G);
	Put(value.B);
	Put(value.A);
}

void NetPacket::NetDataWriter::Put(const FQuat& value)
{
	Put(value.W);
	Put(value.X);
	Put(value.Y);
	Put(value.Z);
}

void NetPacket::NetDataWriter::PutArray(const TArray<FLinearColor>& value)
{
	PutArray<FLinearColor>(value);
}

void NetPacket::NetDataWriter::PutArray(const TArray<FTransform>& value)
{
	PutArray<FTransform>(value);
}

void NetPacket::NetDataWriter::PutArray(const TArray<FMatrix>& value)
{
	PutArray<FMatrix>(value);
}

void NetPacket::NetDataWriter::PutArray(const TArray<FBox>& value)
{
	PutArray<FBox>(value);
}

void NetPacket::NetDataWriter::PutArray(const TArray<FTimespan>& value)
{
	PutArray<FTimespan>(value);
}

void NetPacket::NetDataWriter::PutArray(const TArray<FDateTime>& value)
{
	PutArray<FDateTime>(value);
}

void NetPacket::NetDataWriter::PutArray(const TArray<FRotator>& value)
{
	PutArray<FRotator>(value);
}

void NetPacket::NetDataWriter::PutArray(const TArray<FVector2D>& value)
{
	PutArray<FVector2D>(value);
}

void NetPacket::NetDataWriter::PutArray(const TArray<FIntPoint>& value)
{
	PutArray<FIntPoint>(value);
}

void NetPacket::NetDataWriter::PutArray(const TArray<FColor>& value)
{
	PutArray<FColor>(value);
}

void NetPacket::NetDataWriter::PutArray(const TArray<FQuat>& value)
{
	PutArray<FQuat>(value);
}

void NetPacket::NetDataWriter::PutArray(const TArray<int64>& value)
{
	PutArray<int64>(value);
}

void NetPacket::NetDataWriter::PutArray(const TArray<int32>& value)
{
	PutArray<int32>(value);
}

void NetPacket::NetDataWriter::PutArray(const TArray<uint8>& value)
{
	PutArray<uint8>(value);
}

void NetPacket::NetDataWriter::PutArray(const TArray<FVector>& value)
{
	PutArray<FVector>(value);
}

void NetPacket::NetDataWriter::PutArray(const TArray<FString>& value)
{
	uint16_t length = value.Num();
	Put(length);
	for (int i = 0; i < length; i++)
		Put(value[i]);
}

void NetPacket::NetDataWriter::PutArray(const TArray<FName>& value)
{
	uint16_t length = value.Num();
	Put(length);  // 写入数组的长度

	for (int i = 0; i < length; i++)
	{
		// 将 FName 转换为 FString，然后写入
		FString str = value[i].ToString();
		Put(str);  // 写入字符串
	}
}

void NetPacket::NetDataWriter::PutArray(const TArray<FText>& value)
{
	uint16_t length = value.Num();
	Put(length);  // 写入数组的长度

	for (int i = 0; i < length; i++)
	{
		// 将 FText 转换为 FString，然后写入
		FString str = value[i].ToString();
		Put(str);  // 写入字符串
	}
}
#endif