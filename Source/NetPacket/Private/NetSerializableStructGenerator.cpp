#include "nppch.h"
#include "NetSerializableStructGenerator.h"


namespace NetPacket
{
	void NetSerializableStructGenerator::Generate(const std::string& input, const std::string output)
	{
		std::ifstream inputFile(input);
		if (!inputFile.is_open()) {
			// �ļ���ʧ��
			return;
		}

		// ��ȡ�����ļ�����
		std::string content((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
		inputFile.close();

		// ѡ��NetStructConfig���ɴ���


		std::ofstream outputFile(output);
		if (outputFile.is_open()) {
			// �����ɵ�����д�� .hpp �ļ�
			outputFile << content;
			outputFile.close();
		}
	}

	void NetSerializableStructGenerator::GenerateAll(const std::string& inputDir, const std::string& outputDir)
	{
		// ���� inputDir �µ����� .np �ļ�
		for (const auto& entry : std::filesystem::directory_iterator(inputDir)) {
			if (entry.is_regular_file() && entry.path().extension() == ".np") {
				// ��ȡ�ļ�������·��
				std::string inputFilePath = entry.path().string();

				// ��������ļ���·�����滻 .np ��׺Ϊ .hpp
				std::string outputFilePath = outputDir + "/" + entry.path().stem().string() + ".hpp";

				// ���� Generate �����ļ�����
				Generate(inputFilePath, outputFilePath);
			}
		}
	}


	void NetSerializableStructGenerator::DeclareData(std::stringstream& sst, const std::string& T, const std::string& name, int32_t mode)
	{
		if (mode == 0)
		{
			sst << "\t\t" << T << " " << name << "\n";
		}
		else if (mode == 1)
		{

		}
	}

	void NetSerializableStructGenerator::DeclareDataArray(std::stringstream& sst, const std::string& T, const std::string& name, const int32_t length, int32_t mode)
	{
		if (mode == 0)
		{
			sst << "\t\t" << T << " " << name << "[" << length << "]" << "\n";
		}
		else if (mode == 1)
		{

		}
	}

	void NetSerializableStructGenerator::WriteData(std::stringstream& sst, const std::string& name, int32_t mode)
	{
		if (mode == 0)
		{
			sst << "\t\t\twriter.Put(" << name << ");\n";
		}
		else if (mode == 1)
		{

		}
	}

	void NetSerializableStructGenerator::WriteDataArray(std::stringstream& sst, const std::string& name, int32_t mode)
	{
		if (mode == 0)
		{
			sst << "\t\t\twriter.PutArray(" << name << ");\n";
		}
		else if (mode == 1)
		{

		}
	}

	void NetSerializableStructGenerator::ReadData(std::stringstream& sst, const std::string& name, int32_t mode)
	{
		if (mode == 0)
		{
			sst << "\t\t\treader.Get(" << name << ");\n";
		}
		else if (mode == 1)
		{

		}
	}

	void NetSerializableStructGenerator::ReadDataArray(std::stringstream& sst, const std::string& name, int32_t mode)
	{
		if (mode == 0)
		{
			sst << "\t\t\treader.GetArray(" << name << ");\n";
		}
		else if (mode == 1)
		{

		}
	}

}
