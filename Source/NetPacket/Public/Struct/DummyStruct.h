#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"


#include "DummyStruct.generated.h"
USTRUCT(BlueprintType)
struct FDummyStruct
{
	GENERATED_BODY()
public:
	virtual ~FDummyStruct() = default; // �������������
};


