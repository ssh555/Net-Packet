#pragma once
#pragma warning(push)
#pragma warning(disable:4251)

#include <string>

namespace NetPacket
{
	// 生成文件均为头文件
	// 输入文件格式为json -> 模板文件见 Config/template.np
	class NP_API NetSerializableStructGenerator
	{
	public:
		// 都需要带后缀
		// 返回mode
		int Generate(const std::string& input, const std::string output);

		// 输入文件夹中 *.np
		// 输出文件夹中 *.hpp
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
		std::stringstream uebptypefunctions;
		std::stringstream uebpstd_typefunctions;
		std::stringstream uebptypehash;
		std::stringstream uebpustructfunctions;
	};

	// 代码生成模板
	struct NP_API NetStructConfig
	{
		static const std::string DefaultConfig;
		static const std::string UEConfig;

		static const std::string UEBaseStruct;
		static const std::string UEDummyStruct;
		static const std::string UEBPAPI;
		static const std::string UEBPCONVERT;
		static const std::string UEBPTYPEFuntion;
		static const std::string UEBPSTD_TYPEFuntion;
		static const std::string UEBPTYPEHASH;
		static const std::string UENPSTRUCTREF;
		static const std::string UENPGetUStruct;

	};
}
#pragma warning(pop)