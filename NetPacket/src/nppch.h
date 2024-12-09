#pragma once
#include <stdexcept>  // 引入 std::exception
#include <iostream>
#include <string>
#include <vector>
#include <thread>

#ifdef NP_BUILD_DLL
#define NP_API __declspec(dllexport)
#else
#define NP_API __declspec(dllimport)
#endif

// 头文件声明，源文件实现，加上NP_API即可

NP_API std::string GetNPVersion();

#define STR(S) #S
#define INTERFACE class

class DummyClass
{

};

// UE
#if WITH_EDITOR
#include "CoreMinimal.h"
#include "UObject/Object.h"

#define NP_UE_API ERROR: 没有补充对应的UE_API

#define NP_UFUNCTION(...) UFUNCTION(__VA_ARGS__)
#define NP_UFPROPERTY(...) UFPROPERTY(__VA_ARGS__)
#define NP_UCLASS(...) UCLASS(__VA_ARGS__)
#define NP_UMETA(...) UMETA(__VA_ARGS__)
#define NP_UENUM(...) UENUM(__VA_ARGS__)
#define NP_USTRUCT(...) USTRUCT(__VA_ARGS__)
#define NP_UINTERFACE(...) UINTERFACE(__VA_ARGS__)
#define NP_UDELEGATE(...) UDELEGATE(__VA_ARGS__)

#define  NP_GENERATED_BODY() GENERATED_BODY()
#define NP_GENERATE(CLASS) STR(CLASS##.generated.h)
#else
#define NP_UFUNCTION(...)
#define NP_UFPROPERTY(...)
#define NP_UCLASS(...)
#define NP_UMETA(...)
#define NP_UENUM(...)
#define NP_USTRUCT(...)
#define NP_UINTERFACE(...)
#define NP_UDELEGATE(...)

#define  NP_GENERATED_BODY()
#define NP_GENERATE(CLASS) include STR(CLASS##.generated.h)
#define NP_UE_API
#endif

