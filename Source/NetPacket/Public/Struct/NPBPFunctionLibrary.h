#pragma once
#include "CoreMinimal.h"
#include "DummyStruct.h"
#include <functional>
#include "../NetDataReader.h"
#include <Kismet/BlueprintFunctionLibrary.h>
#include "NPStruct.h"
#include "NPStructRef.h"

#include "NPBPFunctionLibrary.generated.h"


DECLARE_DYNAMIC_DELEGATE_TwoParams(FRegisterProcessDelegate, int32, clienID, UNPStructRef*, data);

UCLASS()
class NP_API UNPBPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "NPCast")
	static void ConvertTotemplate_ue(const UNPStructRef* Parent, Ftemplate_ue& data)
	{
		data = *static_cast<Ftemplate_ue*>(Parent->obj);
	}

};


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
				data->obj = static_cast<FDummyStruct*>(static_cast<Ftemplate_ue*>(obj));

				Delegate.ExecuteIfBound(clienID, data);
			};
		}
	};
}



