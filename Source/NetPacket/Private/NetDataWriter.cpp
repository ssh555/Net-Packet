#include "nppch.h"
#include "NetDataWriter.h"

constexpr size_t NetPacket::UNetDataWriter::InitialSize;

NetPacket::UNetDataWriter::UNetDataWriter(bool autoResize /*= true*/, int32_t initialSize /*= InitialSize*/) : _position(0), _autoResize(autoResize), _data(new uint8_t[initialSize]), _dataSize(initialSize)
{

}

int32_t NetPacket::UNetDataWriter::Capacity() const
{
	return _dataSize;
}

const uint8_t* NetPacket::UNetDataWriter::Data() const
{
	return _data;
}

uint8_t NetPacket::UNetDataWriter::Length() const
{
	return _position;
}

void NetPacket::UNetDataWriter::ResizeIfNeed(int32_t newSize)
{
	if (_dataSize < newSize) {
		resize(std::max(newSize, _dataSize * 2));
	}
}

void NetPacket::UNetDataWriter::EnsureFit(int32_t additionalSize)
{
	if (_dataSize < _position + additionalSize) {
		resize(std::max(_position + additionalSize, _dataSize * 2));
	}
}

void NetPacket::UNetDataWriter::Reset(int32_t size /*= 0*/)
{
	ResizeIfNeed(size);
	_position = 0;
}

uint8_t* NetPacket::UNetDataWriter::CopyData() const
{
	uint8_t* resultData = new uint8_t[_position];
	std::memcpy(resultData, _data, _position);
	return resultData;
}

int32_t NetPacket::UNetDataWriter::SetPosition(int32_t position)
{
	int32_t prevPosition = _position;
	_position = position;
	return prevPosition;
}

void NetPacket::UNetDataWriter::Put(float value)
{
	ResizeIfNeed(_position + sizeof(float));
	std::memcpy(_data + _position, &value, sizeof(float));
	_position += sizeof(float);
}

void NetPacket::UNetDataWriter::Put(const uint8_t* data, const int size)
{
	ResizeIfNeed(_position + size);
	std::memcpy(_data + _position, data, size);
	_position += size;
}

void NetPacket::UNetDataWriter::Put(const uint8_t* data, int32_t offset, int32_t length)
{
	ResizeIfNeed(_position + length);
	std::memcpy(_data + _position, data + offset, length);
	_position += length;
}

void NetPacket::UNetDataWriter::Put(const std::string& value)
{
	uint16_t size = static_cast<uint16_t>(value.size());
	ResizeIfNeed(_position + size + sizeof(uint16_t));
	std::memcpy(_data + _position, &size, sizeof(uint16_t));
	_position += sizeof(uint16_t);
	std::memcpy(_data + _position, value.c_str(), size);
	_position += size;
}

void NetPacket::UNetDataWriter::Put(uint8_t value)
{
	ResizeIfNeed(_position + sizeof(uint8_t));
	_data[_position] = value;
	_position += sizeof(uint8_t);
}

void NetPacket::UNetDataWriter::Put(int8_t value)
{
	ResizeIfNeed(_position + sizeof(int8_t));
	_data[_position] = value;
	_position += sizeof(int8_t);
}

void NetPacket::UNetDataWriter::Put(uint16_t value)
{
	ResizeIfNeed(_position + sizeof(uint16_t));
	std::memcpy(_data + _position, &value, sizeof(uint16_t));
	_position += sizeof(uint16_t);
}

void NetPacket::UNetDataWriter::Put(int16_t value)
{
	ResizeIfNeed(_position + sizeof(int16_t));
	std::memcpy(_data + _position, &value, sizeof(int16_t));
	_position += sizeof(int16_t);
}

void NetPacket::UNetDataWriter::Put(uint32_t value)
{
	ResizeIfNeed(_position + sizeof(uint32_t));
	std::memcpy(_data + _position, &value, sizeof(uint32_t));
	_position += sizeof(uint32_t);
}

void NetPacket::UNetDataWriter::Put(int32_t value)
{
	ResizeIfNeed(_position + sizeof(int32_t));
	std::memcpy(_data + _position, &value, sizeof(int32_t));
	_position += sizeof(int32_t);
}

void NetPacket::UNetDataWriter::Put(uint64_t value)
{
	ResizeIfNeed(_position + sizeof(uint64_t));
	std::memcpy(_data + _position, &value, sizeof(uint64_t));
	_position += sizeof(uint64_t);
}

void NetPacket::UNetDataWriter::Put(int64_t value)
{
	ResizeIfNeed(_position + sizeof(int64_t));
	std::memcpy(_data + _position, &value, sizeof(int64_t));
	_position += sizeof(int64_t);
}

void NetPacket::UNetDataWriter::Put(double value)
{
	ResizeIfNeed(_position + sizeof(double));
	std::memcpy(_data + _position, &value, sizeof(double));
	_position += sizeof(double);
}

void NetPacket::UNetDataWriter::Put(char value)
{
	ResizeIfNeed(_position + sizeof(char));
	std::memcpy(_data + _position, &value, sizeof(char));
	_position += sizeof(char);
}

void NetPacket::UNetDataWriter::Put(std::byte value)
{
	ResizeIfNeed(_position + sizeof(std::byte));
	std::memcpy(_data + _position, &value, sizeof(std::byte));
	_position += sizeof(std::byte);
}

void NetPacket::UNetDataWriter::Put(bool value)
{
	ResizeIfNeed(_position + sizeof(bool));
	std::memcpy(_data + _position, &value, sizeof(bool));
	_position += sizeof(bool);
}

void NetPacket::UNetDataWriter::resize(int32_t size)
{
	delete[] _data;
	_data = new uint8_t[size];
	_dataSize = size;
}

NetPacket::UNetDataWriter NetPacket::UNetDataWriter::FromBytes(uint8_t* bytes, int32_t size, bool copy)
{
	if (copy)
	{
		auto netDataWriter = new UNetDataWriter(true, size);
		netDataWriter->Put(bytes);
		return netDataWriter;
	}
	UNetDataWriter* netDataWriter = new UNetDataWriter(true, 0);
	netDataWriter->_data = bytes;
	netDataWriter->_dataSize = size;
	netDataWriter->_position = size;
	return netDataWriter;
}

NetPacket::UNetDataWriter NetPacket::UNetDataWriter::FromBytes(uint8_t* bytes, int32_t offset, int32_t length)
{
	UNetDataWriter* netDataWriter = new UNetDataWriter(true, length);
	netDataWriter->Put(bytes, offset, length);
	return netDataWriter;
}

NetPacket::UNetDataWriter NetPacket::UNetDataWriter::FromString(std::string value)
{
	auto netDataWriter = new UNetDataWriter();
	netDataWriter->Put(value);
	return netDataWriter;
}

NetPacket::UNetDataWriter NetPacket::UNetDataWriter::FromString(const std::string& value)
{
	auto netDataWriter = new UNetDataWriter();
	netDataWriter->Put(value);
	return netDataWriter;
}

void NetPacket::UNetDataWriter::PutArray(const std::string* value, unsigned short length)
{
	Put(length);
	for (int i = 0; i < length; i++)
		Put(value[i]);
}
