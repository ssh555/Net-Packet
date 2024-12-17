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
	//	// ���ô����ί��
	//	//delegate.ExecuteIfBound(clienID, data);
	//}

	// ������ͼί���¼�������C++���ã�Ȼ����Processor��ע�ᡣ������ͼ��ʹ�ã���Ҫ�����ٷ�װһ��
	// UFUNCTION(BlueprintCallable, Category = "NPBPFunction")
	static std::function<void(int16_t, const INetSerializable&)> WrapDelegate(FRegisterProcessDelegate Delegate)
	{
		// �� Lambda ������װ��ͼί��
		return [Delegate](int16_t clienID, const INetSerializable& obj)
		{
			// ������ͼί��
			Delegate.ExecuteIfBound(clienID, dynamic_cast<FDummtStruct>(obj));
		};
	}
};


