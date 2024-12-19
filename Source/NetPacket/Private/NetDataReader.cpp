#include "nppch.h"
#include "NetDataReader.h"
#include "NetDataWriter.h"
#include "FastBitConverter.h"

NetPacket::NetDataReader::NetDataReader() : _position(0), _dataSize(0), _data(nullptr)
{

}

NetPacket::NetDataReader::NetDataReader(NetDataWriter writer) : _position(0), _dataSize(0), _data(nullptr)
{
	SetSource(writer);
}

NetPacket::NetDataReader::NetDataReader(uint8_t* source, int32_t size) : _position(0), _dataSize(0), _data(nullptr)
{
	SetSource(source, size);
}

NetPacket::NetDataReader::NetDataReader(uint8_t* source, int32_t offset, int32_t maxSize) : _position(0), _dataSize(0), _data(nullptr)
{
	SetSource(source, offset, maxSize);
}


NetPacket::NetDataReader::~NetDataReader()
{
	// 不需要delete，不属于reader的数据，若需要，调用Clear
	//delete _data;
	_data = nullptr;
}



void NetPacket::NetDataReader::Clear(bool isDelete)
{
	_position = 0;
	_dataSize = 0;
	if (isDelete)
		delete[] _data;
	_data = nullptr;
}

int32_t NetPacket::NetDataReader::AvailableBytes() const
{
	return _dataSize - _position;
}

void NetPacket::NetDataReader::Get(uint8_t& value)
{
	if (_position + 1 <= _dataSize) {
		value = _data[_position++];
	}
	else
		throw std::out_of_range("No enough data to get byte");
}

void NetPacket::NetDataReader::Get(std::byte& value)
{
	if (_position + 1 <= _dataSize) {
		value = static_cast<std::byte>(_data[_position++]);
	}
	else
		throw std::out_of_range("No enough data to get byte");
}

void NetPacket::NetDataReader::Get(char& value)
{
	if (_position + 1 <= _dataSize) {
		value = static_cast<char>(_data[_position++]);
	}
	else
		throw std::out_of_range("No enough data to get byte");
}

void NetPacket::NetDataReader::Get(INetSerializable& value)
{
	value.Deserialize(*this);
}

void NetPacket::NetDataReader::Get(int8_t& value)
{
	if (_position + 1 <= _dataSize) {
		value = static_cast<int8_t>(_data[_position++]);
	}
	else
		throw std::out_of_range("No enough data to get sbyte");
}

void NetPacket::NetDataReader::Get(bool& value)
{
	if (_position + 1 <= _dataSize) {
		value = (_data[_position++] != 0);
	}
	else
		throw std::out_of_range("No enough data to get bool");
}

void NetPacket::NetDataReader::Get(int16_t& value)
{
	if (_position + 2 <= _dataSize) {
		FastBitConverter::Get(_data, _position, value);
		_position += 2;
	}
	else
		throw std::out_of_range("No enough data to get short");
}

void NetPacket::NetDataReader::Get(uint16_t& value)
{
	if (_position + 2 <= _dataSize) {
		FastBitConverter::Get(_data, _position, value);
		_position += 2;
	}
	else
		throw std::out_of_range("No enough data to get ushort");
}

void NetPacket::NetDataReader::Get(int32_t& value)
{
	if (_position + 4 <= _dataSize) {
		FastBitConverter::Get(_data, _position, value);
		_position += 4;
	}
	else
		throw std::out_of_range("No enough data to get int");
}

void NetPacket::NetDataReader::Get(uint32_t& value)
{
	if (_position + 4 <= _dataSize) {
		FastBitConverter::Get(_data, _position, value);
		_position += 4;
	}
	else
		throw std::out_of_range("No enough data to get uint");
}

void NetPacket::NetDataReader::Get(int64_t& value)
{
	if (_position + 8 <= _dataSize) {
		FastBitConverter::Get(_data, _position, value);
		_position += 8;
	}
	else
		throw std::out_of_range("No enough data to get long");
}

void NetPacket::NetDataReader::Get(uint64_t& value)
{
	if (_position + 8 <= _dataSize) {
		FastBitConverter::Get(_data, _position, value);
		_position += 8;
	}
	else
		throw std::out_of_range("No enough data to get ulong");
}

void NetPacket::NetDataReader::Get(float& value)
{
	if (_position + 4 <= _dataSize) {
		FastBitConverter::Get(_data, _position, value);
		_position += 4;
	}
	else
		throw std::out_of_range("No enough data to get float");
}

void NetPacket::NetDataReader::Get(double& value)
{
	if (_position + 8 <= _dataSize) {
		FastBitConverter::Get(_data, _position, value);
		_position += 8;
	}
	else
		throw std::out_of_range("No enough data to get double");
}

void NetPacket::NetDataReader::Get(std::string& value)
{
	int32_t length = static_cast<int32_t>(PeekUShort());
	if (_position + 2 + length <= _dataSize) {
		value = reinterpret_cast<char*>(&_data[_position + 2]);
		_position += 2 + length;
	}
	else
		throw std::out_of_range("No enough data to get string");
}

uint16_t NetPacket::NetDataReader::GetArray(uint8_t* data)
{
	return GetArray<uint8_t>(data);
}

uint16_t NetPacket::NetDataReader::GetArray(std::byte* data)
{
	return GetArray<std::byte>(data);
}

uint16_t NetPacket::NetDataReader::GetArray(char* data)
{
	return GetArray<char>(data);
}

uint16_t NetPacket::NetDataReader::GetArray(double* data)
{
	return GetArray<double>(data);
}

uint16_t NetPacket::NetDataReader::GetArray(float* data)
{
	return GetArray<float>(data);
}

uint16_t NetPacket::NetDataReader::GetArray(uint64_t* data)
{
	return GetArray<uint64_t>(data);
}

uint16_t NetPacket::NetDataReader::GetArray(int64_t* data)
{
	return GetArray<int64_t>(data);
}

uint16_t NetPacket::NetDataReader::GetArray(uint32_t* data)
{
	return GetArray<uint32_t>(data);
}

uint16_t NetPacket::NetDataReader::GetArray(int32_t* data)
{
	return GetArray<int32_t>(data);
}

uint16_t NetPacket::NetDataReader::GetArray(uint16_t* data)
{
	return GetArray<uint16_t>(data);
}

uint16_t NetPacket::NetDataReader::GetArray(int16_t* data)
{
	return GetArray<int16_t>(data);
}

uint16_t NetPacket::NetDataReader::GetArray(bool* data)
{
	return GetArray<bool>(data);
}

uint16_t NetPacket::NetDataReader::GetArray(int8_t* data)
{
	return GetArray<int8_t>(data);
}

uint16_t NetPacket::NetDataReader::GetArray(INetSerializable* value)
{
	int32_t size = sizeof(*value);
	uint16_t length = PeekUShort();
	for (int i = 0; i < length; ++i)
	{
		value[i].Deserialize(*this);
	}
	return length;
	//throw std::out_of_range("No enough data to get array");
}

uint16_t NetPacket::NetDataReader::GetArray(std::string* data)
{
	uint16_t length = PeekUShort();
	for (uint16_t i = 0; i < length; i++)
	{
		Get(data[i]);
	}
	return length;
}

uint16_t NetPacket::NetDataReader::PeekUShort(bool isPop)
{
	if (isPop)
	{
		uint16_t value;
		Get(value);
		return value;
	}
	else
	{
		uint16_t value;
		if (_position + 2 <= _dataSize) {
			std::memcpy(&value, &_data[_position], sizeof(value));
			return value;
		}
		else
			throw std::out_of_range("No enough data to get ushort");
	}
	return 0;
}

const uint8_t* NetPacket::NetDataReader::GetRawData()
{
	return _data;
}

int32_t NetPacket::NetDataReader::GetRawDataSize()
{
	return _dataSize;
}

int32_t NetPacket::NetDataReader::GetPosition()
{
	return _position;
}

bool NetPacket::NetDataReader::EndOfData()
{
	return _position == _dataSize;
}

void NetPacket::NetDataReader::SkipBytes(int32_t count)
{
	_position += count;
}

void NetPacket::NetDataReader::SetPosition(int32_t position)
{
	_position = position;
}

void NetPacket::NetDataReader::SetSource(NetDataWriter& dataWriter)
{
	_data = const_cast<uint8_t*>(dataWriter.Data());
	_position = 0;
	_dataSize = dataWriter.Length();
}

void NetPacket::NetDataReader::SetSource(uint8_t* source, int32_t size)
{
	_data = source;
	_position = 0;
	_dataSize = size;
}

void NetPacket::NetDataReader::SetSource(uint8_t* source, int32_t offset, int32_t maxSize)
{
	_data = source;
	_position = offset;
	_dataSize = maxSize;
}

uint8_t* NetPacket::NetDataReader::GetRemainingBytes()
{
	uint8_t* outgoingData = new uint8_t[AvailableBytes()];
	memcpy(&outgoingData, &_data[_position], AvailableBytes());
	_position = _dataSize;
	return outgoingData;
}

#if NP_UE_SUPPORT
void NetPacket::NetDataReader::Get(FLinearColor& value)
{
	Get(value.R);
	Get(value.G);
	Get(value.B);
	Get(value.A);
}

void NetPacket::NetDataReader::Get(FTransform& value)
{
	FVector pos;
	FQuat rot;
	FVector scale;
	Get(pos);
	Get(rot);
	Get(scale);
	value.SetLocation(pos);
	value.SetRotation(rot);
	value.SetScale3D(scale);
}

void NetPacket::NetDataReader::Get(FMatrix& value)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			Get(value.M[i][j]);
		}
	}
}

void NetPacket::NetDataReader::Get(FBox& value)
{
	Get(value.Min);
	Get(value.Max);
}

void NetPacket::NetDataReader::Get(FTimespan& value)
{
	int64 ticks;
	Get(ticks);
	value = ticks;
}

void NetPacket::NetDataReader::Get(FDateTime& value)
{
	int64 ticks;
	Get(ticks);
	value = ticks;
}

void NetPacket::NetDataReader::Get(FRotator& value)
{
	Get(value.Pitch);
	Get(value.Yaw);
	Get(value.Roll);
}

void NetPacket::NetDataReader::Get(FVector2D& value)
{
	Get(value.X);
	Get(value.Y);
}

void NetPacket::NetDataReader::Get(FIntPoint& value)
{
	Get(value.X);
	Get(value.Y);
}

void NetPacket::NetDataReader::Get(FColor& value)
{
	Get(value.R);
	Get(value.G);
	Get(value.B);
	Get(value.A);
}

void NetPacket::NetDataReader::Get(FQuat& value)
{
	Get(value.W);
	Get(value.X);
	Get(value.Y);
	Get(value.Z);
}

void NetPacket::NetDataReader::Get(FVector& value)
{
	Get(value.X);
	Get(value.Y);
	Get(value.Z);
}

void NetPacket::NetDataReader::Get(FString& value)
{
	int32_t length = static_cast<int32_t>(PeekUShort());  // 获取字符串的长度

	if (_position + length <= _dataSize) {
		// 将 UTF-8 字符串转换为 FString
		FString result = FString(UTF8_TO_TCHAR(&_data[_position]));

		value = result;
		_position += length;  // 更新读取位置
	}
	else {
		throw std::out_of_range("Not enough data to get FString");
	}
}

void NetPacket::NetDataReader::Get(FText& value)
{
	FString str;
	Get(str);
	value.FromString(str);
}

void NetPacket::NetDataReader::Get(FName& value)
{
	FString str;
	Get(str);
	value = FName(str);
}

uint16_t NetPacket::NetDataReader::GetArray(TArray<FLinearColor>& value)
{
	return GetArray<FLinearColor>(value);
}

uint16_t NetPacket::NetDataReader::GetArray(TArray<FTransform>& value)
{
	return GetArray<FTransform>(value);

}

uint16_t NetPacket::NetDataReader::GetArray(TArray<FMatrix>& value)
{
	return GetArray<FMatrix>(value);
}

uint16_t NetPacket::NetDataReader::GetArray(TArray<FBox>& value)
{
	return GetArray<FBox>(value);
}

uint16_t NetPacket::NetDataReader::GetArray(TArray<FTimespan>& value)
{
	return GetArray<FTimespan>(value);
}

uint16_t NetPacket::NetDataReader::GetArray(TArray<FDateTime>& value)
{
	return GetArray<FDateTime>(value);
}

uint16_t NetPacket::NetDataReader::GetArray(TArray<FRotator>& value)
{
	return GetArray<FRotator>(value);
}

uint16_t NetPacket::NetDataReader::GetArray(TArray<FVector2D>& value)
{
	return GetArray<FVector2D>(value);
}

uint16_t NetPacket::NetDataReader::GetArray(TArray<FIntPoint>& value)
{
	return GetArray<FIntPoint>(value);
}

uint16_t NetPacket::NetDataReader::GetArray(TArray<FColor>& value)
{
	return GetArray<FColor>(value);
}

uint16_t NetPacket::NetDataReader::GetArray(TArray<FQuat>& value)
{
	return GetArray<FQuat>(value);
}

uint16_t NetPacket::NetDataReader::GetArray(TArray<FVector>& value)
{
	return GetArray<FVector>(value);
}

uint16_t NetPacket::NetDataReader::GetArray(TArray<int64>& value)
{
	return GetArray<int64>(value);
}

uint16_t NetPacket::NetDataReader::GetArray(TArray<int32>& value)
{
	return GetArray<int32>(value);
}

uint16_t NetPacket::NetDataReader::GetArray(TArray<uint8>& value)
{
	return GetArray<uint8>(value);
}

uint16_t NetPacket::NetDataReader::GetArray(TArray<FString>& value)
{
	uint16_t length = PeekUShort();  // 获取数组的长度
	//value.SetNumUninitialized(length);  // 为数组分配空间

	for (uint16_t i = 0; i < length; i++)
	{
		FString tmp;
		Get(tmp);  // 读取每个 FString 到数组中
		value.Add(tmp);
	}

	return length;
}

uint16_t NetPacket::NetDataReader::GetArray(TArray<FName>& value)
{
	uint16_t length = PeekUShort();  // 获取数组的长度
	value.SetNumUninitialized(length);  // 为数组分配空间

	for (uint16_t i = 0; i < length; i++)
	{
		Get(value[i]);
	}

	return length;
}

uint16_t NetPacket::NetDataReader::GetArray(TArray<FText>& value)
{
	uint16_t length = PeekUShort();  // 获取数组的长度
	//value.SetNumUninitialized(length);  // 为数组分配空间

	for (uint16_t i = 0; i < length; i++)
	{
		FText tmp;
		Get(tmp);
		value.Add(tmp);
	}

	return length;
}

#endif