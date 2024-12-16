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
	char buffer[MAX_PATH];  // �� char ����洢·��
	DWORD len = GetModuleFileNameA(NULL, buffer, MAX_PATH);  // ʹ�� GetModuleFileNameA ��ȡ·��
	if (len == 0) {
		std::cerr << "Error retrieving module path: " << GetLastError() << std::endl;
		return "";
	}
	return fs::path(buffer).parent_path().string();  // ��ȡ·������
}
void printUsage() {
	std::cout << "Usage: StructFileGenerator [-i <input_dir>] [-o <output_dir>]\n";
	std::cout << "  -i <input_dir>  : ����Ŀ¼ (Ĭ��: ./Input)\n";
	std::cout << "  -o <output_dir> : ���Ŀ¼ (Ĭ��: ./Generate)\n";
}

int main(int argc, char* argv[]) {
	// ʹ�� EXE ����Ŀ¼��ΪĬ��·��
	std::string exeDir = getExecutableDirectory();
	std::string inputDir = exeDir + "/Input"; // Ĭ������Ŀ¼
	std::string outputDir = exeDir + "/Generate"; // Ĭ�����Ŀ¼

	// ���������в���
	for (int i = 1; i < argc; ++i) {
		if (std::strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
			inputDir = argv[++i]; // ��ȡ����Ŀ¼
		}
		else if (std::strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
			outputDir = argv[++i]; // ��ȡ���Ŀ¼
		}
		else {
			std::cerr << "δ֪����: " << argv[i] << std::endl;
			printUsage();
			return 1;
		}
	}

	// ȷ������Ŀ¼����
	if (!fs::exists(inputDir)) {
		std::cerr << "����Ŀ¼������: " << inputDir << std::endl;
		return 1;
	}

	// ȷ�����Ŀ¼����
	if (!fs::exists(outputDir)) {
		if (!fs::create_directory(outputDir)) {
			std::cerr << "�������Ŀ¼ʧ��: " << outputDir << std::endl;
			return 1;
		}
	}

	// �����ȡ���Ĳ���
	std::cout << "����Ŀ¼: " << inputDir << std::endl;
	std::cout << "���Ŀ¼: " << outputDir << std::endl;

	// TODO: ���ɽṹ���ļ����߼�
	// ������ִ�д���Ŀ¼�������ļ����߼����������д�� outputDir Ŀ¼
	NetPacket::NetSerializableStructGenerator generator;

	generator.GenerateAll(inputDir, outputDir);

	//system("pause");
	return 0;
}
