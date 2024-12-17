#pragma once
#include <string>

namespace NetPacket
{
	// �����ļ���Ϊͷ�ļ�
	// �����ļ���ʽΪjson -> ģ���ļ��� Config/template.np
	class NP_API NetSerializableStructGenerator
	{
	private:


	public:
		// ����Ҫ����׺
		// ����mode
		int Generate(const std::string& input, const std::string output);

		// �����ļ����� *.np
		// ����ļ����� *.hpp
		void GenerateAll(const std::string& inputDir, const std::string& outputDir);

	private:
		// mode: 0 - default
		// mode: 1 - ue
		void DeclareData(std::stringstream& sst, const std::string& T, const std::string& name, int32_t mode);
		void DeclareDataArray(std::stringstream& sst, const std::string& T, const std::string& name, const int32_t length, int32_t mode);

		void WriteData(std::stringstream& sst, const std::string& name, int32_t mode);
		void WriteDataArray(std::stringstream& sst, const std::string& name, const int32_t length, int32_t mode);

		void ReadData(std::stringstream& sst, const std::string& name, int32_t mode);
		void ReadDataArray(std::stringstream& sst, const std::string& name, int32_t mode);

		std::string GetConfigTemplate(int32_t mode);

		std::stringstream uebpfunctions;
	};

	// ��������ģ��
	struct NetStructConfig
	{
		static const std::string DefaultConfig;
		static const std::string UEConfig;

		static const std::string UEDummyStruct;
		static const std::string UEBPAPI;
		static const std::string UEBPCONVERT;
		static const std::string UENPSTRUCTREF;

	};
}
