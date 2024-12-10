#include "nppch.h"
#include "INetSerializable.h"
#include "NetDataWriter.h"
#include "NetDataReader.h"

namespace NetPacket
{
	// MurmurHash16 �㷨
	inline static uint16_t MurmurHash16(const std::string& str) {
		const uint32_t seed = 0x1234ABCD;  // ���ѡһ������
		uint32_t hash = seed;

		const uint8_t* data = reinterpret_cast<const uint8_t*>(str.c_str());
		size_t length = str.size();

		const uint32_t m = 0x5bd1e995; // ����
		const int r = 16; // 16λ���

		uint32_t h = hash ^ length;

		// 4�ֽ�Ϊһ����м���
		while (length >= 4) {
			uint32_t k = *(reinterpret_cast<const uint32_t*>(data));

			k *= m;
			k ^= k >> r;
			k *= m;

			h *= m;
			h ^= k;

			data += 4;
			length -= 4;
		}

		// ����ʣ����ֽ�
		if (length == 3) {
			h ^= static_cast<uint32_t>(data[2]) << 16;
		}
		if (length >= 2) {
			h ^= static_cast<uint32_t>(data[1]) << 8;
		}
		if (length >= 1) {
			h ^= static_cast<uint32_t>(data[0]);
		}

		// ���յĻ�Ϻ���СΪ16λ
		h *= m;
		h ^= h >> r;
		h *= m;

		return static_cast<uint16_t>(h & 0xFFFF); // �ض�Ϊ16λ
	}

	uint16_t INetSerializable::GetTypeHash() const
	{
		std::string typeName = typeid(*this).name();
		return MurmurHash16(typeName);
	}

}