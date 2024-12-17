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

	int NetSerializableStructGenerator::Generate(const std::string& input, const std::string output)
	{
		std::ifstream inputFile(input);
		if (!inputFile.is_open()) {
			// �ļ���ʧ��
			return -1;
		}

		// ��ȡ�����ļ�����
		std::string content((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
		inputFile.close();
		// ���ɴ���
		json j = json::parse(content);


		// ѡ��NetStructConfig���ɴ���
		std::string CLASSNAME;
		std::stringstream INCLUDES;
		std::stringstream DECLATEDATA;
		std::stringstream WRITERDATA;
		std::stringstream READRDATA;
		int mode;

		CLASSNAME = j["classname"];
		mode = j["mode"];

		std::string outContent = GetConfigTemplate(mode);

		// includes
		INCLUDES << "// ������Զ����������͵�ͷ�ļ�\n";
		for (auto& el : j["includes"])
		{
			INCLUDES << "#include " << el["name"] << "\n";
		}
		// basedata
		DECLATEDATA << "\t\t// ����������\n";
		WRITERDATA << "\t\t\t// ����������\n";
		READRDATA << "\t\t\t// ����������\n";
		for (auto& el : j["basedata"])
		{
			DeclareData(DECLATEDATA, el["type"], el["name"], mode);
			WriteData(WRITERDATA, el["name"], mode);
			ReadData(READRDATA, el["name"], mode);
		}
		DECLATEDATA << "\n";
		WRITERDATA << "\n";
		READRDATA << "\n";
		// arraydata
		DECLATEDATA << "\t\t// ��������\n";
		WRITERDATA << "\t\t\t// ��������\n";
		READRDATA << "\t\t\t// ��������\n";
		for (auto& el : j["arraydata"])
		{
			DeclareDataArray(DECLATEDATA, el["type"], el["name"], el["length"], mode);
			WriteDataArray(WRITERDATA, el["name"], el["length"], mode);
			ReadDataArray(READRDATA, el["name"], mode);
		}
		DECLATEDATA << "\n";
		WRITERDATA << "\n";
		READRDATA << "\n";

		replaceAll(outContent, "{INCLUDES}", INCLUDES.str());
		replaceAll(outContent, "{DECLATEDATA}", DECLATEDATA.str());
		replaceAll(outContent, "{WRITERDATA}", WRITERDATA.str());
		replaceAll(outContent, "{READRDATA}", READRDATA.str());
		// ����滻
		replaceAll(outContent, "{CLASSNAME}", CLASSNAME);

		std::ofstream outputFile(output);
		if (outputFile.is_open()) {
			// �����ɵ�����д�� .hpp �ļ�
			outputFile << outContent;
			outputFile.close();
		}
		return mode;
	}

	void NetSerializableStructGenerator::GenerateAll(const std::string& inputDir, const std::string& outputDir)
	{
		// ������Ŀ¼������NPStruct.h���������е�ͷ�ļ�
		std::string output = outputDir + "/NPStruct.h";
		std::ofstream outputFile(output);

		bool bIsUE = false;
		// ���� inputDir �µ����� .np �ļ�
		for (const auto& entry : std::filesystem::directory_iterator(inputDir)) {
			if (entry.is_regular_file() && entry.path().extension() == ".np") {
				// ��ȡ�ļ�������·��
				std::string inputFilePath = entry.path().string();

				// ��������ļ���·�����滻 .np ��׺Ϊ .hpp
				std::string outputFilePath = outputDir + "/" + entry.path().stem().string() + ".h";

				if (outputFile.is_open()) {
					// �����ɵ�����д�� .hpp �ļ�
					outputFile << "#include \"" << entry.path().stem().string() + ".h\"\n";
				}

				std::cout << "�����ļ�:" << entry.path().stem().string() + ".np" << std::endl;
				// ���� Generate �����ļ�����
				int mode = Generate(inputFilePath, outputFilePath);
				if (mode == 1)
				{
					bIsUE = true;
				}
			}
		}
		outputFile.close();

		// ��Ŀ���ļ��������� DummyStruct
		if (bIsUE)
		{
			output = outputDir + "/DummyStruct.h";
			outputFile.open(output);
			outputFile << NetStructConfig::UEDummyStruct;
		}
	}


	void NetSerializableStructGenerator::DeclareData(std::stringstream& sst, const std::string& T, const std::string& name, int32_t mode)
	{
		if (mode == 0)
		{
			sst << "\t\t" << T << " " << name << ";\n";
		}
		else if (mode == 1)
		{
			sst << "\tUPROPERTY(BlueprintReadWrite, EditAnywhere, Category = \"{CLASSNAME}\")\n";
			sst << "\t" << T << " " << name << ";\n";
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
			sst << "\tUPROPERTY(BlueprintReadWrite, EditAnywhere, Category = \"{CLASSNAME}\")\n";
			sst << "\tTArray<" << T << "> " << name << ";\n";
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
			sst << "\t\twriter.Put(" << name << ");\n";
		}
	}

	void NetSerializableStructGenerator::WriteDataArray(std::stringstream& sst, const std::string& name, const int32_t length, int32_t mode)
	{
		if (mode == 0)
		{
			sst << "\t\\ttwriter.PutArray(" << name << ", " << length << ");\n";
		}
		else if (mode == 1)
		{
			sst << "\t\twriter.PutArray(" << name << ");\n";
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
			sst << "\t\treader.Get(" << name << ");\n";
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
			sst << "\t\treader.GetArray(" << name << ");\n";
		}
	}


	std::string NetSerializableStructGenerator::GetConfigTemplate(int32_t mode)
	{
		if (mode == 0)
		{
			return NetStructConfig::DefaultConfig;
		}
		else if (mode == 1)
		{
			return NetStructConfig::UEConfig;
		}
		throw new std::exception("mode error: ������Чmode");
	}

	const std::string NetStructConfig::DefaultConfig = R"(#pragma once
#include "../nppch.h"
// ��������޸�includeΪ���Լ�����ȷ·��
#include "../INetSerializable.h"
#include "../NetDataWriter.h"
#include "../NetDataReader.h"
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

		virtual uint16_t GetTypeHash() const override
		{
			return MurmurHash16("{CLASSNAME}");
		}
	};
}
)";

	const std::string NetStructConfig::UEConfig = R"(#pragma once
#include "CoreMinimal.h"
// ��������޸�includeΪ���Լ�����ȷ·��
#include "../NetDataWriter.h"
#include "../NetDataReader.h"
#include "../INetSerializable.h"
#include "UObject/NoExportTypes.h"
#include "DummyStruct.h"

{INCLUDES}

#include "{CLASSNAME}.generated.h"
USTRUCT(BlueprintType, Blueprintable)
struct NP_API F{CLASSNAME} : public FDummyStruct, public NetPacket::INetSerializable
{
	GENERATED_BODY()

public:
{DECLATEDATA}

public:
	// ʵ�� Serialize ����
	virtual void Serialize(NetPacket::NetDataWriter& writer) const override
	{
		writer.Put(GetTypeHash());
{WRITERDATA}
	}

	virtual void Deserialize(NetPacket::NetDataReader& reader) override
	{
		reader.PeekUShort();
{READRDATA}
	}

	virtual uint16_t GetTypeHash() const override
	{
		return MurmurHash16("{CLASSNAME}");
	}
};

)";

	const std::string NetStructConfig::UEDummyStruct = R"(#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"


#include "DummyStruct.generated.h"
USTRUCT()
struct FDummyStruct
{
	GENERATED_BODY()
public:
	virtual ~FDummyStruct() = default; // �������������
};


)";

}
