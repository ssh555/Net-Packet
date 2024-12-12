#include "nppch.h"
#include "NetSerializableStructGenerator.h"


namespace NetPacket
{
	inline void replaceAll(std::string& str, const std::string& from, const std::string& to) {
		size_t startPos = 0;
		while ((startPos = str.find(from, startPos)) != std::string::npos) {
			str.replace(startPos, from.length(), to);
			startPos += to.length(); // ��ֹ�����滻���滻�Ĳ���
		}
	}

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
		// ���ɴ���
		json j = json::parse(content);

		std::string outContent = NetStructConfig::DefaultConfig;

		// ѡ��NetStructConfig���ɴ���
		std::string CLASSNAME;
		std::stringstream INCLUDES;
		std::stringstream DECLATEDATA;
		std::stringstream WRITERDATA;
		std::stringstream READRDATA;
		int mode;

		CLASSNAME = j["classname"];
		mode = j["mode"];
		// includes
		for (auto& el : j["includes"])
		{
			INCLUDES << "#include " << el["name"] << "\n";
		}
		// basedata
		for (auto& el : j["basedata"])
		{
			DeclareData(DECLATEDATA, el["type"], el["name"], mode);
			WriteData(WRITERDATA, el["name"], mode);
			ReadData(READRDATA, el["name"], mode);
		}
		// arraydata
		for (auto& el : j["arraydata"])
		{
			DeclareDataArray(DECLATEDATA, el["type"], el["name"], el["length"], mode);
			WriteDataArray(WRITERDATA, el["name"], el["length"], mode);
			ReadDataArray(READRDATA, el["name"], mode);
		}

		replaceAll(outContent, "{CLASSNAME}", CLASSNAME);
		replaceAll(outContent, "{INCLUDES}", INCLUDES.str());
		replaceAll(outContent, "{DECLATEDATA}", DECLATEDATA.str());
		replaceAll(outContent, "{WRITERDATA}", WRITERDATA.str());
		replaceAll(outContent, "{READRDATA}", READRDATA.str());

		std::ofstream outputFile(output);
		if (outputFile.is_open()) {
			// �����ɵ�����д�� .hpp �ļ�
			outputFile << outContent;
			outputFile.close();
		}
	}

	void NetSerializableStructGenerator::GenerateAll(const std::string& inputDir, const std::string& outputDir)
	{
		// ������Ŀ¼������NPStruct.h���������е�ͷ�ļ�
		std::string output = outputDir + "/NPStruct.h";
		std::ofstream outputFile(output);


		// ���� inputDir �µ����� .np �ļ�
		for (const auto& entry : std::filesystem::directory_iterator(inputDir)) {
			if (entry.is_regular_file() && entry.path().extension() == ".np") {
				// ��ȡ�ļ�������·��
				std::string inputFilePath = entry.path().string();

				// ��������ļ���·�����滻 .np ��׺Ϊ .hpp
				std::string outputFilePath = outputDir + "/" + entry.path().stem().string() + ".hpp";

				if (outputFile.is_open()) {
					// �����ɵ�����д�� .hpp �ļ�
					outputFile << "#include \"" << entry.path().stem().string() + ".hpp\"\n";
				}

				std::cout << "�����ļ�:" << entry.path().stem().string() << std::endl;
				// ���� Generate �����ļ�����
				Generate(inputFilePath, outputFilePath);
			}
		}
		outputFile.close();
	}


	void NetSerializableStructGenerator::DeclareData(std::stringstream& sst, const std::string& T, const std::string& name, int32_t mode)
	{
		if (mode == 0)
		{
			sst << "\t\t" << T << " " << name << ";\n";
		}
		else if (mode == 1)
		{

		}
	}

	void NetSerializableStructGenerator::DeclareDataArray(std::stringstream& sst, const std::string& T, const std::string& name, const int32_t length, int32_t mode)
	{
		if (mode == 0)
		{
			sst << "\t\t" << T << " " << name << "[" << length << "]" << ";\n";
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

	void NetSerializableStructGenerator::WriteDataArray(std::stringstream& sst, const std::string& name, const int32_t length, int32_t mode)
	{
		if (mode == 0)
		{
			sst << "\t\t\twriter.PutArray(" << name << "," << length << ");\n";
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


	const std::string NetStructConfig::DefaultConfig = R"(#pragma once
#include "nppch.h"
#include "INetSerializable.h"
#include "NetDataWriter.h"
#include "NetDataReader.h"
{INCLUDES}

namespace NetPacket
{
	class NP_API {CLASSNAME} : public INetSerializable
	{
	public:
{DECLATEDATA}

	public:
		virtual void Serialize(NetDataWriter& writer) const override
		{
			writer.Put(GetTypeHash());
{WRITERDATA}
		}

		virtual void Deserialize(NetDataReader& reader) override
		{
			reader.PeekUShort();
{READRDATA}
		}
	};
}
)";

	const std::string NetStructConfig::UEConfig = "";

}
