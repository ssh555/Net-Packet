#pragma once
#include <stdexcept>  // ���� std::exception
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <filesystem>
#include <fstream>
#include <sstream>

#include <Json/include/single_include/nlohmann/json.hpp>
#include <Json/include/single_include/nlohmann/json_fwd.hpp>
using json = nlohmann::json;
#if NP_UE_SUPPORT
#define NP_API
#elif NP_BUILD_DLL
#define NP_API __declspec(dllexport)
#else
#define NP_API __declspec(dllimport)
#endif

// ͷ�ļ�������Դ�ļ�ʵ�֣�����NP_API����
NP_API std::string GetNPVersion();

#define INTERFACE class


