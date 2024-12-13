#pragma once
#include "CoreMinimal.h"
#include "NetDataWriter.h"
#include "NetDataReader.h"
#include "INetSerializable.h"
#include "UObject/NoExportTypes.h"


#include "DummyStruct.generated.h"
USTRUCT(BlueprintType, Blueprintable)
struct FDummyStruct
{
	GENERATED_BODY()
public:
	virtual ~FDummyStruct() = default; // 添加虚析构函数
};


