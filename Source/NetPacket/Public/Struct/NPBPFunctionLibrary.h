#pragma once
#include "CoreMinimal.h"
#include "DummyStruct.h"
#include <functional>
#include "../NetDataReader.h"
#include <Kismet/BlueprintFunctionLibrary.h>
#include "NPStruct.h"
#include "NPStructRef.h"
#include "NetPacketProcessor.h"

#include "NPBPFunctionLibrary.generated.h"
DECLARE_DYNAMIC_DELEGATE_TwoParams(FRegisterProcessDelegate, int32, clientID, UNPStructRef*, ref);

namespace NetPacket
{
	class NP_API NPFunctionLibrary
	{
		public:

		// 包裹蓝图委托事件，用于C++调用，然后在Processor中注册。若在蓝图中使用，需要自行再封装一层
		// UFUNCTION(BlueprintCallable, Category = "NPBPFunction")
		static std::function<void(int16_t, INetSerializable*)> WrapDelegate(FRegisterProcessDelegate Delegate)
		{
			// 用 Lambda 函数包装蓝图委托
			return [Delegate](int16_t clienID, INetSerializable* obj)
			{
				// 调用蓝图委托
				UNPStructRef* data = NewObject<UNPStructRef>();
				data->obj = static_cast<FDummyStruct*>(obj);

				Delegate.ExecuteIfBound(clienID, data);
			};
		}
	};
}


UCLASS()
class NP_API UNPBPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "NPCast")
	static UNPStructRef* CreateRef()
	{
		return NewObject<UNPStructRef>();
	}


	UFUNCTION(BlueprintCallable, Category = "NPCast")
	static UStruct* GetUStructPtr_template_ue()
	{
		return Ftemplate_ue::StaticStruct();
	}



	UFUNCTION(BlueprintCallable, Category = "NPCast")
	static void ConvertTotemplate_ue(const UNPStructRef* Parent, Ftemplate_ue& data)
	{
		data = *static_cast<Ftemplate_ue*>(Parent->obj);
	}

	UFUNCTION(BlueprintCallable, Category = "NPCast")
	static UNPStructRef* Converttemplate_ueToDummyStruct(const Ftemplate_ue& data)
	{
		UNPStructRef* ref = CreateRef();
		ref->Set(static_cast<const FDummyStruct&>(data));
		return ref;
	}


	static void Register(NetPacket::NetPacketProcessor& processor, UStruct* structType, FRegisterProcessDelegate Delegate)
	{
		if (structType == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("UStruct cannot be nullptr!"));
			return;
		}
		else if (structType == Ftemplate_ue::StaticStruct())
		{
			processor.Register<Ftemplate_ue>(Ftemplate_ue::GetTypeHash(), NetPacket::NPFunctionLibrary::WrapDelegate(Delegate));
		}

		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Unknown struct type!"));
		}
	}

	static void Register(NetPacket::NetPacketProcessor& processor, UStruct* structType, std::function<void(int16_t, NetPacket::INetSerializable*)> Delegate)
	{
		if (structType == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("UStruct cannot be nullptr!"));
			return;
		}
		else if (structType == Ftemplate_ue::StaticStruct())
		{
			processor.Register<Ftemplate_ue>(Ftemplate_ue::GetTypeHash(), Delegate);
		}

		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Unknown struct type!"));
		}
	}

	static uint16_t GetTypeHash(UStruct* structType)
	{
		if (structType == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("UStruct cannot be nullptr!"));
			return 0;
		}
		else if (structType == Ftemplate_ue::StaticStruct())
		{
			return Ftemplate_ue::GetTypeHash();
		}

		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Unknown struct type!"));
		}
		return 0;
	}

};
