#pragma once
#include <string>

namespace NetPacket
{
	// �����ļ���Ϊͷ�ļ�
	// �����ļ���ʽΪjson
	class NP_API NetSerializableStructGenerator
	{
	private:


	public:
		// ����Ҫ����׺
		void Generate(const std::string& input, const std::string output);

		// �����ļ����� *.np
		// ����ļ����� *.hpp
		void GenerateAll(const std::string& inputDir, const std::string& outputDir);
	};

	// ��������ģ��
	struct NetStructConfig
	{
		static const std::string DefaultConfig;
		static const std::string UEConfig;
	};
}
