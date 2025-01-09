#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseStruct.h"
#include "INetSerializable.h"

#include "DummyStruct.generated.h"
USTRUCT(BlueprintType)
struct FDummyStruct : public FBaseStruct, public NetPacket::INetSerializable
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString GUID;

	virtual ~FDummyStruct() = default; // �������������

	virtual void Serialize(NetPacket::NetDataWriter& writer) const override
	{
		throw new std::exception("������࣬����ʹ��");
	}

	virtual void Deserialize(NetPacket::NetDataReader& reader) override
	{
		throw new std::exception("������࣬����ʹ��");
	}

	virtual uint16_t GetTypeHashID() const override
	{
		throw new std::exception("������࣬����ʹ��");
	}

	static uint16_t GetTypeHash()
	{
		throw new std::exception("������࣬����ʹ��");
	}
};


