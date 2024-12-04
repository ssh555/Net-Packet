#pragma once
#include <stdexcept>  // 引入 std::exception

#ifdef NP_BUILD_DLL
#define NP_API __declspec(dllexport)
#else
#define NP_API __declspec(dllimport)
#endif

// 其他项目使用时需包含这个头文件
extern "C" {
	// 需要至少有一个导出保证生成 *.lib 才能保证其他其他链接时才能正常使用
	// 需要导出或者导入的函数或类
	NP_API void __Dummy__();

}
