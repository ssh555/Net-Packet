#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"


#include "DummyStruct.generated.h"
USTRUCT()
struct FDummyStruct
{
	GENERATED_BODY()
public:
	virtual ~FDummyStruct() = default; // 添加虚析构函数
};


