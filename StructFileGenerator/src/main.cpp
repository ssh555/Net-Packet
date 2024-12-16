#include <nppch.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <cstdlib>  // For std::exit
#include <cstring>  // For std::strcmp
#include <windows.h> // For GetModuleFileName
#include "NetSerializableStructGenerator.h"

//#include "Struct/NPStruct.h"


namespace fs = std::filesystem;

std::string getExecutableDirectory() {
	char buffer[MAX_PATH];  // 用 char 数组存储路径
	DWORD len = GetModuleFileNameA(NULL, buffer, MAX_PATH);  // 使用 GetModuleFileNameA 获取路径
	if (len == 0) {
		std::cerr << "Error retrieving module path: " << GetLastError() << std::endl;
		return "";
	}
	return fs::path(buffer).parent_path().string();  // 获取路径部分
}
void printUsage() {
	std::cout << "Usage: StructFileGenerator [-i <input_dir>] [-o <output_dir>]\n";
	std::cout << "  -i <input_dir>  : 输入目录 (默认: ./Input)\n";
	std::cout << "  -o <output_dir> : 输出目录 (默认: ./Generate)\n";
}

int main(int argc, char* argv[]) {
	// 使用 EXE 所在目录作为默认路径
	std::string exeDir = getExecutableDirectory();
	std::string inputDir = exeDir + "/Input"; // 默认输入目录
	std::string outputDir = exeDir + "/Generate"; // 默认输出目录

	// 解析命令行参数
	for (int i = 1; i < argc; ++i) {
		if (std::strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
			inputDir = argv[++i]; // 获取输入目录
		}
		else if (std::strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
			outputDir = argv[++i]; // 获取输出目录
		}
		else {
			std::cerr << "未知参数: " << argv[i] << std::endl;
			printUsage();
			return 1;
		}
	}

	// 确保输入目录存在
	if (!fs::exists(inputDir)) {
		std::cerr << "输入目录不存在: " << inputDir << std::endl;
		return 1;
	}

	// 确保输出目录存在
	if (!fs::exists(outputDir)) {
		if (!fs::create_directory(outputDir)) {
			std::cerr << "创建输出目录失败: " << outputDir << std::endl;
			return 1;
		}
	}

	// 输出获取到的参数
	std::cout << "输入目录: " << inputDir << std::endl;
	std::cout << "输出目录: " << outputDir << std::endl;

	// TODO: 生成结构体文件的逻辑
	// 在这里执行处理目录中数据文件的逻辑，并将结果写入 outputDir 目录
	NetPacket::NetSerializableStructGenerator generator;

	generator.GenerateAll(inputDir, outputDir);

	//system("pause");
	return 0;
}
