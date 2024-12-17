#pragma once
#pragma once

#include "CoreMinimal.h"
#include "FDummtStruct.h"
#include <functional>
#include "../NetDataReader.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "NPBPFunctionLibrary.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FRegisterProcessDelegate, int32, clienID, const FDummtStruct&, data);

UCLASS()
class NP_API UNPBPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	//UFUNCTION(BlueprintCallable, Category = "NPBPFunction")
	//static void CallDelegateWithParams(FRegisterProcessDelegate Delegate, int32 clienID, const FDummtStruct& data)
	//{
	//	// 调用传入的委托
	//	//delegate.ExecuteIfBound(clienID, data);
	//}

	// 包裹蓝图委托事件，用于C++调用，然后在Processor中注册。若在蓝图中使用，需要自行再封装一层
	// UFUNCTION(BlueprintCallable, Category = "NPBPFunction")
	static std::function<void(int16_t, const INetSerializable&)> WrapDelegate(FRegisterProcessDelegate Delegate)
	{
		// 用 Lambda 函数包装蓝图委托
		return [Delegate](int16_t clienID, const INetSerializable& obj)
		{
			// 调用蓝图委托
			Delegate.ExecuteIfBound(clienID, dynamic_cast<FDummtStruct>(obj));
		};
	}
};


