#pragma once
#include <stdexcept>  // ÒýÈë std::exception
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <mutex>
#include <functional>

//#include "Struct/NPStruct.h"

#include "Json/include/single_include/nlohmann/json.hpp"
#include "Json/include/single_include/nlohmann/json_fwd.hpp"
using json = nlohmann::json;
#ifdef NP_UE_SUPPORT
#define NP_API __declspec(dllexport)
#else
#ifdef NP_BUILD_DLL
#define NP_API __declspec(dllexport)
#else
#define NP_API __declspec(dllimport)
#endif
#endif





