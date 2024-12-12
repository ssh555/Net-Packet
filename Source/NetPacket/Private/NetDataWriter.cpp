#include "nppch.h"
#include "NetDataWriter.h"

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

uint8_t NetPacket::NetDataWriter::Length() const
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
	std::memcpy(_data + _position, &value, sizeof(float));
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
	ResizeIfNeed(_position + size + sizeof(uint16_t));
	std::memcpy(_data + _position, &size, sizeof(uint16_t));
	_position += sizeof(uint16_t);
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
	std::memcpy(_data + _position, &value, sizeof(uint16_t));
	_position += sizeof(uint16_t);
}

void NetPacket::NetDataWriter::Put(int16_t value)
{
	ResizeIfNeed(_position + sizeof(int16_t));
	std::memcpy(_data + _position, &value, sizeof(int16_t));
	_position += sizeof(int16_t);
}

void NetPacket::NetDataWriter::Put(uint32_t value)
{
	ResizeIfNeed(_position + sizeof(uint32_t));
	std::memcpy(_data + _position, &value, sizeof(uint32_t));
	_position += sizeof(uint32_t);
}

void NetPacket::NetDataWriter::Put(int32_t value)
{
	ResizeIfNeed(_position + sizeof(int32_t));
	std::memcpy(_data + _position, &value, sizeof(int32_t));
	_position += sizeof(int32_t);
}

void NetPacket::NetDataWriter::Put(uint64_t value)
{
	ResizeIfNeed(_position + sizeof(uint64_t));
	std::memcpy(_data + _position, &value, sizeof(uint64_t));
	_position += sizeof(uint64_t);
}

void NetPacket::NetDataWriter::Put(int64_t value)
{
	ResizeIfNeed(_position + sizeof(int64_t));
	std::memcpy(_data + _position, &value, sizeof(int64_t));
	_position += sizeof(int64_t);
}

void NetPacket::NetDataWriter::Put(double value)
{
	ResizeIfNeed(_position + sizeof(double));
	std::memcpy(_data + _position, &value, sizeof(double));
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
	ResizeIfNeed(_position + sizeof(int16_t) + value.Len() * sizeof(TCHAR));

	int16_t strLength = value.Len();
	FMemory::Memcpy(_data + _position, &strLength, sizeof(int16_t));
	_position += sizeof(int16_t);

	FMemory::Memcpy(_data + _position, value.GetCharArray().GetData(), strLength * sizeof(TCHAR));
	_position += strLength * sizeof(TCHAR);
}

void NetPacket::NetDataWriter::Put(const FVector& value)
{
	ResizeIfNeed(_position + sizeof(FVector));
	FMemory::Memcpy(_data + _position, &value, sizeof(FVector));
	_position += sizeof(FVector);
}

void NetPacket::NetDataWriter::Put(const FLinearColor& value)
{
	ResizeIfNeed(_position + sizeof(FLinearColor));
	FMemory::Memcpy(_data + _position, &value, sizeof(FLinearColor));
	_position += sizeof(FLinearColor);
}

void NetPacket::NetDataWriter::Put(const FTransform& value)
{
	ResizeIfNeed(_position + sizeof(FTransform));
	FMemory::Memcpy(_data + _position, &value, sizeof(FTransform));
	_position += sizeof(FTransform);
}

void NetPacket::NetDataWriter::Put(const FMatrix& value)
{
	ResizeIfNeed(_position + sizeof(FMatrix));
	FMemory::Memcpy(_data + _position, &value, sizeof(FMatrix));
	_position += sizeof(FMatrix);
}

void NetPacket::NetDataWriter::Put(const FBox& value)
{
	ResizeIfNeed(_position + sizeof(FBox));
	FMemory::Memcpy(_data + _position, &value, sizeof(FBox));
	_position += sizeof(FBox);
}

void NetPacket::NetDataWriter::Put(const FTimespan& value)
{
	ResizeIfNeed(_position + sizeof(FTimespan));
	FMemory::Memcpy(_data + _position, &value, sizeof(FTimespan));
	_position += sizeof(FTimespan);
}

void NetPacket::NetDataWriter::Put(const FDateTime& value)
{
	ResizeIfNeed(_position + sizeof(FDateTime));
	FMemory::Memcpy(_data + _position, &value, sizeof(FDateTime));
	_position += sizeof(FDateTime);
}

void NetPacket::NetDataWriter::Put(const FRotator& value)
{
	ResizeIfNeed(_position + sizeof(FRotator));
	FMemory::Memcpy(_data + _position, &value, sizeof(FRotator));
	_position += sizeof(FRotator);
}

void NetPacket::NetDataWriter::Put(const FVector2D& value)
{
	ResizeIfNeed(_position + sizeof(FVector2D));
	FMemory::Memcpy(_data + _position, &value, sizeof(FVector2D));
	_position += sizeof(FVector2D);
}

void NetPacket::NetDataWriter::Put(const FIntPoint& value)
{
	ResizeIfNeed(_position + sizeof(FIntPoint));
	FMemory::Memcpy(_data + _position, &value, sizeof(FIntPoint));
	_position += sizeof(FIntPoint);
}

void NetPacket::NetDataWriter::Put(const FColor& value)
{
	ResizeIfNeed(_position + sizeof(FColor));
	FMemory::Memcpy(_data + _position, &value, sizeof(FColor));
	_position += sizeof(FColor);
}

void NetPacket::NetDataWriter::Put(const FQuat& value)
{
	ResizeIfNeed(_position + sizeof(FQuat));
	FMemory::Memcpy(_data + _position, &value, sizeof(FQuat));
	_position += sizeof(FQuat);
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
#endif