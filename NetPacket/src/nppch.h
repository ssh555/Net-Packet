#pragma once
#include <stdexcept>  // ���� std::exception

#ifdef NP_BUILD_DLL
#define NP_API __declspec(dllexport)
#else
#define NP_API __declspec(dllimport)
#endif

// ������Ŀʹ��ʱ��������ͷ�ļ�
extern "C" {
	// ��Ҫ������һ��������֤���� *.lib ���ܱ�֤������������ʱ��������ʹ��
	// ��Ҫ�������ߵ���ĺ�������
	NP_API void __Dummy__();

}
