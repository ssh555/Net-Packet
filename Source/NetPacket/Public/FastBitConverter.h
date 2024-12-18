#pragma once

namespace NetPacket {

	// ����Bitת����
	class NP_API FastBitConverter {
	public:
		// ��ȡָ�����͵��ֽڱ�ʾ
		template <typename T>
		static void Put(uint8_t* bytes, int startIndex, T value);

		// ת�����������ڲ�ͬ���͵����ݣ�ulong, double, int, float �ȣ�
		static void Put(uint8_t* bytes, int startIndex, double value);
		static void Put(uint8_t* bytes, int startIndex, float value);
		static void Put(uint8_t* bytes, int startIndex, short value);
		static void Put(uint8_t* bytes, int startIndex, unsigned short value);
		static void Put(uint8_t* bytes, int startIndex, int value);
		static void Put(uint8_t* bytes, int startIndex, unsigned int value);
		static void Put(uint8_t* bytes, int startIndex, long long value);
		static void Put(uint8_t* bytes, int startIndex, unsigned long long value);


		// ���ֽ������ȡֵ����ֵ������
		template <typename T>
		static void Get(const uint8_t* bytes, int startIndex, T& value);

		// ��Բ�ͬ���͵� Get ����
		static void Get(const uint8_t* bytes, int startIndex, double& value);
		static void Get(const uint8_t* bytes, int startIndex, float& value);
		static void Get(const uint8_t* bytes, int startIndex, short& value);
		static void Get(const uint8_t* bytes, int startIndex, unsigned short& value);
		static void Get(const uint8_t* bytes, int startIndex, int& value);
		static void Get(const uint8_t* bytes, int startIndex, unsigned int& value);
		static void Get(const uint8_t* bytes, int startIndex, long long& value);
		static void Get(const uint8_t* bytes, int startIndex, unsigned long long& value);



	private:
		// ���ڽ�����ת��Ϊ�ֽڱ�ʾ��С�˸�ʽ
		static void WriteLittleEndian(uint8_t* buffer, int offset, uint64_t data);
		static void WriteLittleEndian(uint8_t* buffer, int offset, int data);
		static void WriteLittleEndian(uint8_t* buffer, int offset, short data);

		// ��С�˸�ʽ�ֽ������ȡ uint64_t ���͵�����
		static uint64_t ReadLittleEndian64(const uint8_t* buffer, int offset);

		// ��С�˸�ʽ�ֽ������ȡ int ���͵�����
		static int ReadLittleEndian32(const uint8_t* buffer, int offset);

		// ��С�˸�ʽ�ֽ������ȡ short ���͵�����
		static short ReadLittleEndian16(const uint8_t* buffer, int offset);

	};

} // namespace NetPacket
