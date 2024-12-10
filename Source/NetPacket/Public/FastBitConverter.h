#pragma once

namespace NetPacket {

	// ����Bitת����
	class 
#if !NP_UE_SUPPORT
		NP_API
#endif
		FastBitConverter {
	public:
		// ��ȡָ�����͵��ֽڱ�ʾ
		template <typename T>
		static void GetBytes(uint8_t* bytes, int startIndex, T value);

		// ת�����������ڲ�ͬ���͵����ݣ�ulong, double, int, float �ȣ�
		static void GetBytes(uint8_t* bytes, int startIndex, double value);
		static void GetBytes(uint8_t* bytes, int startIndex, float value);
		static void GetBytes(uint8_t* bytes, int startIndex, short value);
		static void GetBytes(uint8_t* bytes, int startIndex, unsigned short value);
		static void GetBytes(uint8_t* bytes, int startIndex, int value);
		static void GetBytes(uint8_t* bytes, int startIndex, unsigned int value);
		static void GetBytes(uint8_t* bytes, int startIndex, long value);
		static void GetBytes(uint8_t* bytes, int startIndex, unsigned long long value);

	private:
		// ���ڽ�����ת��Ϊ�ֽڱ�ʾ��С�˸�ʽ
		static void WriteLittleEndian(uint8_t* buffer, int offset, uint64_t data);
		static void WriteLittleEndian(uint8_t* buffer, int offset, int data);
		static void WriteLittleEndian(uint8_t* buffer, int offset, short data);
	};

} // namespace NetPacket
