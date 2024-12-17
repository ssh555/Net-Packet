#include "nppch.h"
#include "NetSerializableStructGenerator.h"


namespace NetPacket
{
	inline void replaceAll(std::string& str, const std::string& from, const std::string& to) {
		size_t startPos = 0;
		while ((startPos = str.find(from, startPos)) != std::string::npos) {
			str.replace(startPos, from.length(), to);
			startPos += to.length(); // 防止重新替换已替换的部分
		}
	}

	int NetSerializableStructGenerator::Generate(const std::string& input, const std::string output)
	{
		std::ifstream inputFile(input);
		if (!inputFile.is_open()) {
			// 文件打开失败
			return -1;
		}

		// 读取输入文件内容
		std::string content((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
		inputFile.close();
		// 生成代码
		json j = json::parse(content);


		// 选择NetStructConfig生成代码
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
		INCLUDES << "// 需包含自定义数据类型的头文件\n";
		for (auto& el : j["includes"])
		{
			INCLUDES << "#include " << el["name"] << "\n";
		}
		// basedata
		DECLATEDATA << "\t\t// 非数组数据\n";
		WRITERDATA << "\t\t\t// 非数组数据\n";
		READRDATA << "\t\t\t// 非数组数据\n";
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
		DECLATEDATA << "\t\t// 数组数据\n";
		WRITERDATA << "\t\t\t// 数组数据\n";
		READRDATA << "\t\t\t// 数组数据\n";
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
		// 最后替换
		replaceAll(outContent, "{CLASSNAME}", CLASSNAME);

		std::ofstream outputFile(output);
		if (outputFile.is_open()) {
			// 将生成的内容写入 .hpp 文件
			outputFile << outContent;
			outputFile.close();
		}

		// 加入UE蓝图的类型转换函数
		if (mode == 1)
		{
			std::string tmp = NetStructConfig::UEBPCONVERT;
			replaceAll(tmp, "{TYPE}", CLASSNAME);
			uebpfunctions << tmp;
		}
		return mode;
	}

	void NetSerializableStructGenerator::GenerateAll(const std::string& inputDir, const std::string& outputDir)
	{
		uebpfunctions.clear();

		// 在生成目录下生成NPStruct.h，包含所有的头文件
		std::string output = outputDir + "/NPStruct.h";
		std::ofstream outputFile(output);

		outputFile << "#include \"NPBPFunctionLibrary.h\"\n";

		bool bIsUE = false;
		// 遍历 inputDir 下的所有 .np 文件
		for (const auto& entry : std::filesystem::directory_iterator(inputDir)) {
			if (entry.is_regular_file() && entry.path().extension() == ".np") {
				// 获取文件的完整路径
				std::string inputFilePath = entry.path().string();

				// 生成输出文件的路径，替换 .np 后缀为 .hpp
				std::string outputFilePath = outputDir + "/" + entry.path().stem().string() + ".h";

				if (outputFile.is_open()) {
					// 将生成的内容写入 .hpp 文件
					outputFile << "#include \"" << entry.path().stem().string() + ".h\"\n";
				}

				std::cout << "处理文件:" << entry.path().stem().string() + ".np" << std::endl;
				// 调用 Generate 进行文件生成
				int mode = Generate(inputFilePath, outputFilePath);
				if (mode == 1)
				{
					bIsUE = true;
				}
			}
		}
		outputFile.close();

		// 在目标文件夹下生成 DummyStruct
		if (bIsUE)
		{
			output = outputDir + "/DummyStruct.h";
			outputFile.open(output);
			outputFile << NetStructConfig::UEDummyStruct;
			outputFile.close();

			// 生成蓝图函数库
			output = outputDir + "/NPBPFunctionLibrary.h";
			outputFile.open(output);
			std::string o = NetStructConfig::UEBPAPI;
			std::string tmp = uebpfunctions.str();
			replaceAll(o, "{FUNCTION}", tmp);
			outputFile << o;
			outputFile.close();
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
			sst << "\t\t\twriter.PutArray(" << name << ", " << length << ");\n";
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
		throw new std::exception("mode error: 不是有效mode");
	}

	const std::string NetStructConfig::DefaultConfig = R"(#pragma once
#include "../nppch.h"
// 如果报错，修改include为你自己的正确路径
#include "../INetSerializable.h"
#include "../NetDataWriter.h"
#include "../NetDataReader.h"
{INCLUDES}

namespace NetPacket
{
	class {CLASSNAME} : public INetSerializable
	{
	public:
{DECLATEDATA}

	public:
		~{CLASSNAME}() = default;

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

		static uint16_t GetTypeHash()
		{
			return MurmurHash16("{CLASSNAME}");
		}
	};
}
)";

	const std::string NetStructConfig::UEConfig = R"(#pragma once
#include "CoreMinimal.h"
// 如果报错，修改include为你自己的正确路径
#include "../NetDataWriter.h"
#include "../NetDataReader.h"
#include "../INetSerializable.h"
#include "UObject/NoExportTypes.h"
#include "DummyStruct.h"

{INCLUDES}

#include "{CLASSNAME}.generated.h"
USTRUCT(BlueprintType, Blueprintable)
struct F{CLASSNAME} : public FDummyStruct, public NetPacket::INetSerializable
{
	GENERATED_BODY()

public:
{DECLATEDATA}

public:
	~F{CLASSNAME}() = default; // 添加虚析构函数

	// 实现 Serialize 函数
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

	static uint16_t GetTypeHash()
	{
		return MurmurHash16("{CLASSNAME}");
	}
};

)";

	const std::string NetStructConfig::UEDummyStruct = R"(#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"


#include "DummyStruct.generated.h"
USTRUCT(BlueprintType)
struct FDummyStruct
{
	GENERATED_BODY()
public:
	virtual ~FDummyStruct() = default; // 添加虚析构函数
};


)";

	const std::string NetStructConfig::UEBPAPI = R"(#pragma once
#include "CoreMinimal.h"
#include "DummyStruct.h"
#include <functional>
#include "../NetDataReader.h"
#include <Kismet/BlueprintFunctionLibrary.h>
#include "NPStruct.h"

#include "NPBPFunctionLibrary.generated.h"


DECLARE_DYNAMIC_DELEGATE_TwoParams(FRegisterProcessDelegate, int32, clienID, const FDummyStruct&, data);

UCLASS()
class NP_API UNPBPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
{FUNCTION}
};


namespace NetPacket
{
	class NP_API NPFunctionLibrary
	{
	public:

		// 包裹蓝图委托事件，用于C++调用，然后在Processor中注册。若在蓝图中使用，需要自行再封装一层
		// UFUNCTION(BlueprintCallable, Category = "NPBPFunction")
		static std::function<void(int16_t, const INetSerializable&)> WrapDelegate(FRegisterProcessDelegate Delegate)
		{
			// 用 Lambda 函数包装蓝图委托
			return [Delegate](int16_t clienID, const INetSerializable& obj)
			{
				// 调用蓝图委托
				Delegate.ExecuteIfBound(clienID, reinterpret_cast<const FDummyStruct&>(obj));
			};
		}
	};
}



)";

	const std::string NetStructConfig::UEBPCONVERT = R"(
	UFUNCTION(BlueprintCallable, Category = "NPCast")
	static void ConvertTo{TYPE}(const FDummyStruct& Parent, F{TYPE}& data)
	{
		F{TYPE}& obj = *((F{TYPE}*)(&Parent));
		FMemory::Memcpy(data, obj);
	}
)";

}
