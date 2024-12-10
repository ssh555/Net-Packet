#pragma once
#include "nppch.h"

#if NP_UE_SUPPORT
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include NP_GENERATE(NetSerializable)
#endif

namespace NetPacket
{
	class UNetDataWriter;
	class UNetDataReader;

	// INetSerializable ½Ó¿Ú
	INTERFACE NP_API INetSerializable
	{
		NP_GENERATED_BODY()

	public:
		virtual ~INetSerializable() = default;

		NP_UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "NetPacket")
		virtual void Serialize(UNetDataWriter& writer) const = 0;

		NP_UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "NetPacket")
		virtual void Deserialize(UNetDataReader& reader) = 0;
	};
#if NP_UE_SUPPORT
	NP_UINTERFACE(MinimalAPI, BlueprintType, Blueprintable)
	INTERFACE NP_API UNetSerializable : public UInterface
	{
		NP_GENERATED_BODY()
	}
#endif


};
	
