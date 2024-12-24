#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseStruct.h"
#include <INetSerializable.h>

#include "DummyStruct.generated.h"
USTRUCT(BlueprintType)
struct FDummyStruct : public FBaseStruct, public NetPacket::INetSerializable
{
	GENERATED_BODY()
public:
	virtual ~FDummyStruct() = default; // Ìí¼ÓÐéÎö¹¹º¯Êý
	virtual void Serialize(NetPacket::NetDataWriter& writer) const override
	{

	}

	virtual void Deserialize(NetPacket::NetDataReader& reader) override
	{

	}
};


