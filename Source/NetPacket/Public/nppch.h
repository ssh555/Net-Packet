#pragma once
#include <stdexcept>  // ���� std::exception
#include <iostream>
#include <string>
#include <vector>
#include <thread>


#ifdef NP_BUILD_DLL
#define NP_API __declspec(dllexport)
#else
#define NP_API __declspec(dllimport)
#endif

// ͷ�ļ�������Դ�ļ�ʵ�֣�����NP_API����
NP_API std::string GetNPVersion();

#define INTERFACE class


