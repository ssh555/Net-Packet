#include "nppch.h"
#include "NetSerializableStructGenerator.h"


namespace NetPacket
{
	void NetSerializableStructGenerator::Generate(const std::string& input, const std::string output)
	{
		std::ifstream inputFile(input);
		if (!inputFile.is_open()) {
			// 文件打开失败
			return;
		}

		// 读取输入文件内容
		std::string content((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
		inputFile.close();

		// 选择NetStructConfig生成代码


		std::ofstream outputFile(output);
		if (outputFile.is_open()) {
			// 将生成的内容写入 .hpp 文件
			outputFile << content;
			outputFile.close();
		}
	}

	void NetSerializableStructGenerator::GenerateAll(const std::string& inputDir, const std::string& outputDir)
	{
		// 遍历 inputDir 下的所有 .np 文件
		for (const auto& entry : std::filesystem::directory_iterator(inputDir)) {
			if (entry.is_regular_file() && entry.path().extension() == ".np") {
				// 获取文件的完整路径
				std::string inputFilePath = entry.path().string();

				// 生成输出文件的路径，替换 .np 后缀为 .hpp
				std::string outputFilePath = outputDir + "/" + entry.path().stem().string() + ".hpp";

				// 调用 Generate 进行文件生成
				Generate(inputFilePath, outputFilePath);
			}
		}
	}
}
