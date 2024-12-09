#include "nppch.h"
#include "NetDataReader.h"
#include "NetDataWriter.h"

NetPacket::UNetDataReader::UNetDataReader() : _position(0), _dataSize(0), _data(nullptr)
{

}

NetPacket::UNetDataReader::UNetDataReader(UNetDataWriter writer) : _position(0), _dataSize(0), _data(nullptr)
{
	SetSource(writer);
}

NetPacket::UNetDataReader::UNetDataReader(uint8_t* source, int32_t size) : _position(0), _dataSize(0), _data(nullptr)
{
	SetSource(source, size);
}

NetPacket::UNetDataReader::UNetDataReader(uint8_t* source, int32_t offset, int32_t maxSize) : _position(0), _dataSize(0), _data(nullptr)
{
	SetSource(source, offset, maxSize);
}


NetPacket::UNetDataReader::~UNetDataReader()
{
	delete _data;
}



void NetPacket::UNetDataReader::Clear()
{
	_position = 0;
	_dataSize = 0;
	delete[] _data;
}

int32_t NetPacket::UNetDataReader::AvailableBytes() const
{
	return _dataSize - _position;
}

uint8_t NetPacket::UNetDataReader::GetByte()
{
	if (_position + 1 <= _dataSize) {
		return _data[_position++];
	}
	throw std::out_of_range("No enough data to get byte");
}

int8_t NetPacket::UNetDataReader::GetSByte()
{
	if (_position + 1 <= _dataSize) {
		return static_cast<int8_t>(_data[_position++]);
	}
	throw std::out_of_range("No enough data to get sbyte");
}

bool NetPacket::UNetDataReader::GetBool()
{
	if (_position + 1 <= _dataSize) {
		return _data[_position++] != 0;
	}
	throw std::out_of_range("No enough data to get bool");
}

int16_t NetPacket::UNetDataReader::GetShort()
{
	if (_position + 2 <= _dataSize) {
		int16_t value;
		std::memcpy(&value, &_data[_position], sizeof(value));
		_position += 2;
		return value;
	}
	throw std::out_of_range("No enough data to get short");
}

uint16_t NetPacket::UNetDataReader::GetUShort()
{
	if (_position + 2 <= _dataSize) {
		uint16_t value;
		std::memcpy(&value, &_data[_position], sizeof(value));
		_position += 2;
		return value;
	}
	throw std::out_of_range("No enough data to get ushort");
}

int32_t NetPacket::UNetDataReader::GetInt()
{
	if (_position + 4 <= _dataSize) {
		int32_t value;
		std::memcpy(&value, &_data[_position], sizeof(value));
		_position += 4;
		return value;
	}
	throw std::out_of_range("No enough data to get int");
}

uint32_t NetPacket::UNetDataReader::GetUInt()
{
	if (_position + 4 <= _dataSize) {
		uint32_t value;
		std::memcpy(&value, &_data[_position], sizeof(value));
		_position += 4;
		return value;
	}
	throw std::out_of_range("No enough data to get uint");
}

int64_t NetPacket::UNetDataReader::GetLong()
{
	if (_position + 8 <= _dataSize) {
		int64_t value;
		std::memcpy(&value, &_data[_position], sizeof(value));
		_position += 8;
		return value;
	}
	throw std::out_of_range("No enough data to get long");
}

uint64_t NetPacket::UNetDataReader::GetULong()
{
	if (_position + 8 <= _dataSize) {
		uint64_t value;
		std::memcpy(&value, &_data[_position], sizeof(value));
		_position += 8;
		return value;
	}
	throw std::out_of_range("No enough data to get ulong");
}

float NetPacket::UNetDataReader::GetFloat()
{
	if (_position + 4 <= _dataSize) {
		float value;
		std::memcpy(&value, &_data[_position], sizeof(value));
		_position += 4;
		return value;
	}
	throw std::out_of_range("No enough data to get float");
}

double NetPacket::UNetDataReader::GetDouble()
{
	if (_position + 8 <= _dataSize) {
		double value;
		std::memcpy(&value, &_data[_position], sizeof(value));
		_position += 8;
		return value;
	}
	throw std::out_of_range("No enough data to get double");
}

std::string NetPacket::UNetDataReader::GetString()
{
	int32_t length = static_cast<int32_t>(PeekUShort());
	if (_position + 2 + length <= _dataSize) {
		std::string value(reinterpret_cast<char*>(&_data[_position + 2]), length);
		_position += 2 + length;
		return value;
	}
	throw std::out_of_range("No enough data to get string");
}

uint8_t* NetPacket::UNetDataReader::GetBytesWithLength()
{
	int32_t length = static_cast<int32_t>(PeekUShort());
	if (_position + 2 + length <= _dataSize) {
		//std::vector<uint8_t> value(_data.begin() + _position + 2, _data.begin() + _position + 2 + length);
		uint8_t* value = new uint8_t[length];
		memcpy(&value, &_data[_position], sizeof(value));
		_position += 2 + length;
		return value;
	}
	throw std::out_of_range("No enough data to get bytes with length");
}

std::string* NetPacket::UNetDataReader::GetStringArray()
{
	uint16_t length = PeekUShort();
	std::string* arr = new std::string[length];
	for (uint16_t i = 0; i < length; i++)
	{
		arr[i] = GetString();
	}
	return arr;
}

uint16_t NetPacket::UNetDataReader::PeekUShort()
{
	return GetUShort();
}

const uint8_t* NetPacket::UNetDataReader::GetRawData()
{
	return _data;
}

int32_t NetPacket::UNetDataReader::GetRawDataSize()
{
	return _dataSize;
}

int32_t NetPacket::UNetDataReader::GetPosition()
{
	return _position;
}

bool NetPacket::UNetDataReader::EndOfData()
{
	return _position == _dataSize;
}

void NetPacket::UNetDataReader::SkipBytes(int32_t count)
{
	_position += count;
}

void NetPacket::UNetDataReader::SetPosition(int32_t position)
{
	_position = position;
}

void NetPacket::UNetDataReader::SetSource(UNetDataWriter& dataWriter)
{
	_data = const_cast<uint8_t*>(dataWriter.Data());
	_position = 0;
	_dataSize = dataWriter.Length();
}

void NetPacket::UNetDataReader::SetSource(uint8_t* source, int32_t size)
{
	_data = source;
	_position = 0;
	_dataSize = size;
}

void NetPacket::UNetDataReader::SetSource(uint8_t* source, int32_t offset, int32_t maxSize)
{
	_data = source;
	_position = offset;
	_dataSize = maxSize;
}

uint8_t* NetPacket::UNetDataReader::GetRemainingBytes()
{
	uint8_t* outgoingData = new uint8_t[AvailableBytes()];
	memcpy(&outgoingData, &_data[_position], AvailableBytes());
	_position = _dataSize;
	return outgoingData;
}
