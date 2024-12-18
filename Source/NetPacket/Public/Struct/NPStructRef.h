#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <UObject/Object.h>
#include "NPStruct.h"

#include "NPStructRef.generated.h"
UCLASS(Blueprintable, BlueprintType)
class NP_API UNPStructRef : public UObject
{
	GENERATED_BODY()
public:
	FDummyStruct* obj;

	UFUNCTION(BlueprintCallable, Category = "NPStructRef")
	FDummyStruct& Get()
	{
		return *obj;
	}

	UFUNCTION(BlueprintCallable, Category = "NPStructRef")
	void Set(const FDummyStruct& data)
	{
		obj = &const_cast<FDummyStruct&>(data);
	}
};

