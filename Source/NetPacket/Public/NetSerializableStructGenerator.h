#pragma once
#include <string>

namespace NetPacket
{
	// �����ļ���Ϊͷ�ļ�
	// �����ļ���ʽΪjson
	class NetSerializableStructGenerator
	{
	private:
		// ��������ģ��
		static const std::string DefaultConfig;
		static const std::string UEConfig;

	public:
		// ����Ҫ����׺
		void Generate(const std::string& input, const std::string output);

		// �����ļ����� *.np
		// ����ļ����� *.h
		void GenerateAll(const std::string& inputDir, const std::string& outputDir);
	};
}
