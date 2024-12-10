#pragma once
#include <stdexcept>  // 引入 std::exception
#include <iostream>
#include <string>
#include <vector>
#include <thread>

#if NP_UE_SUPPORT
#define NP_API NETPACKET_API
#elif NP_BUILD_DLL
#define NP_API __declspec(dllexport)
#else
#define NP_API __declspec(dllimport)
#endif

// 头文件声明，源文件实现，加上NP_API即可
#if !NP_UE_SUPPORT
NP_API std::string GetNPVersion();
#endif

#define STR(S) #S
#define INTERFACE class

class DummyClass
{

};

// UE
#if NP_UE_SUPPORT
#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "UObject/Object.h"
#include "Engine/Engine.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "UObject/NoExportTypes.h"

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
#endif

