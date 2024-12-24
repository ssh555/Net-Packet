#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseStruct.h"

#include "DummyStruct.generated.h"
USTRUCT(BlueprintType)
struct FDummyStruct : public FBaseStruct, public NetPacket::INetSerializable
{
	GENERATED_BODY()
public:
	virtual ~FDummyStruct() = default; // Ìí¼ÓÐéÎö¹¹º¯Êý
};


