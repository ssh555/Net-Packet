#pragma once
#include "CoreMinimal.h"
#include "DummyStruct.h"
#include <functional>
#include "../NetDataReader.h"
#include <Kismet/BlueprintFunctionLibrary.h>

#include "NPBPFunctionLibrary.generated.h"


DECLARE_DYNAMIC_DELEGATE_TwoParams(FRegisterProcessDelegate, int32, clienID, const FDummyStruct&, data);

UCLASS()
class NP_API UNPBPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "NPCast")
	static void ConvertTotemplate_ue(const FDummyStruct& Parent, Ftemplate_ue& data)
	{
		data = reinterpret_cast<Ftemplate_ue&>(const_cast<FDummyStruct&>(Parent));
	}

};


namespace NetPacket
{
	class NP_API NPFunctionLibrary
	{
	public:

		// 包裹蓝图委托事件，用于C++调用，然后在Processor中注册。若在蓝图中使用，需要自行再封装一层
		// UFUNCTION(BlueprintCallable, Category = "NPBPFunction")
		static std::function<void(int16_t, const INetSerializable&)> WrapDelegate(FRegisterProcessDelegate Delegate)
		{
			// 用 Lambda 函数包装蓝图委托
			return [Delegate](int16_t clienID, const INetSerializable& obj)
			{
				// 调用蓝图委托
				Delegate.ExecuteIfBound(clienID, reinterpret_cast<const FDummyStruct&>(obj));
			};
		}
	};
}



