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

		// ������ͼί���¼�������C++���ã�Ȼ����Processor��ע�ᡣ������ͼ��ʹ�ã���Ҫ�����ٷ�װһ��
		// UFUNCTION(BlueprintCallable, Category = "NPBPFunction")
		static std::function<void(int16_t, const INetSerializable&)> WrapDelegate(FRegisterProcessDelegate Delegate)
		{
			// �� Lambda ������װ��ͼί��
			return [Delegate](int16_t clienID, const INetSerializable& obj)
			{
				// ������ͼί��
				Delegate.ExecuteIfBound(clienID, reinterpret_cast<const FDummyStruct&>(obj));
			};
		}
	};
}



