#include "nppch.h"
#include "NetDataReader.h"
#include "NetDataWriter.h"

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
	if(isDelete)
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
	throw std::out_of_range("No enough data to get byte");
}

void NetPacket::NetDataReader::Get(std::byte& value)
{
	if (_position + 1 <= _dataSize) {
		value = static_cast<std::byte>(_data[_position++]);
	}
	throw std::out_of_range("No enough data to get byte");
}

void NetPacket::NetDataReader::Get(char& value)
{
	if (_position + 1 <= _dataSize) {
		value = static_cast<char>(_data[_position++]);
	}
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
	throw std::out_of_range("No enough data to get sbyte");
}

void NetPacket::NetDataReader::Get(bool& value)
{
	if (_position + 1 <= _dataSize) {
		value = (_data[_position++] != 0);
	}
	throw std::out_of_range("No enough data to get bool");
}

void NetPacket::NetDataReader::Get(int16_t& value)
{
	if (_position + 2 <= _dataSize) {
		std::memcpy(&value, &_data[_position], sizeof(value));
		_position += 2;
	}
	throw std::out_of_range("No enough data to get short");
}

void NetPacket::NetDataReader::Get(uint16_t& value)
{
	if (_position + 2 <= _dataSize) {
		std::memcpy(&value, &_data[_position], sizeof(value));
		_position += 2;
	}
	throw std::out_of_range("No enough data to get ushort");
}

void NetPacket::NetDataReader::Get(int32_t& value)
{
	if (_position + 4 <= _dataSize) {
		std::memcpy(&value, &_data[_position], sizeof(value));
		_position += 4;
	}
	throw std::out_of_range("No enough data to get int");
}

void NetPacket::NetDataReader::Get(uint32_t& value)
{
	if (_position + 4 <= _dataSize) {
		std::memcpy(&value, &_data[_position], sizeof(value));
		_position += 4;
	}
	throw std::out_of_range("No enough data to get uint");
}

void NetPacket::NetDataReader::Get(int64_t& value)
{
	if (_position + 8 <= _dataSize) {
		std::memcpy(&value, &_data[_position], sizeof(value));
		_position += 8;
	}
	throw std::out_of_range("No enough data to get long");
}

void NetPacket::NetDataReader::Get(uint64_t& value)
{
	if (_position + 8 <= _dataSize) {
		std::memcpy(&value, &_data[_position], sizeof(value));
		_position += 8;
	}
	throw std::out_of_range("No enough data to get ulong");
}

void NetPacket::NetDataReader::Get(float& value)
{
	if (_position + 4 <= _dataSize) {
		std::memcpy(&value, &_data[_position], sizeof(value));
		_position += 4;
	}
	throw std::out_of_range("No enough data to get float");
}

void NetPacket::NetDataReader::Get(double& value)
{
	if (_position + 8 <= _dataSize) {
		std::memcpy(&value, &_data[_position], sizeof(value));
		_position += 8;
	}
	throw std::out_of_range("No enough data to get double");
}

void NetPacket::NetDataReader::Get(std::string& value)
{
	int32_t length = static_cast<int32_t>(PeekUShort());
	if (_position + 2 + length <= _dataSize) {
		std::string value(reinterpret_cast<char*>(&_data[_position + 2]), length);
		_position += 2 + length;
	}
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
	throw std::out_of_range("No enough data to get array");
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
		}
		throw std::out_of_range("No enough data to get ushort");
	}
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
