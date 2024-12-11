#pragma once
#include <string>

namespace NetPacket
{
	// 生成文件均为头文件
	// 输入文件格式为json
	class NetSerializableStructGenerator
	{
	private:
		// 代码生成模板
		static const std::string DefaultConfig;
		static const std::string UEConfig;

	public:
		// 都需要带后缀
		void Generate(const std::string& input, const std::string output);

		// 输入文件夹中 *.np
		// 输出文件夹中 *.h
		void GenerateAll(const std::string& inputDir, const std::string& outputDir);
	};
}
