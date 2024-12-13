#pragma once
#include "CoreMinimal.h"
#include "NetDataWriter.h"
#include "NetDataReader.h"
#include "INetSerializable.h"
#include "UObject/NoExportTypes.h"
#include "DummyStruct.h"

// 需包含自定义数据类型的头文件


#include "template_ue.generated.h"
USTRUCT(BlueprintType, Blueprintable)
struct Ftemplate_ue : public FDummyStruct, public NetPacket::INetSerializable
{
	GENERATED_BODY()

public:
		// 非数组数据
	UPROPERTY(BlueprintReadWrite, Category = "template_ue")
	FString str;
	UPROPERTY(BlueprintReadWrite, Category = "template_ue")
	FName strN;
	UPROPERTY(BlueprintReadWrite, Category = "template_ue")
	FText strT;
	UPROPERTY(BlueprintReadWrite, Category = "template_ue")
	int64 i64;
	UPROPERTY(BlueprintReadWrite, Category = "template_ue")
	int32 i32;
	UPROPERTY(BlueprintReadWrite, Category = "template_ue")
	uint8 ui8;
	UPROPERTY(BlueprintReadWrite, Category = "template_ue")
	FVector vec;
	UPROPERTY(BlueprintReadWrite, Category = "template_ue")
	FQuat q;
	UPROPERTY(BlueprintReadWrite, Category = "template_ue")
	FColor color;
	UPROPERTY(BlueprintReadWrite, Category = "template_ue")
	FIntPoint intp;
	UPROPERTY(BlueprintReadWrite, Category = "template_ue")
	FVector2D vec2d;
	UPROPERTY(BlueprintReadWrite, Category = "template_ue")
	FRotator rot;
	UPROPERTY(BlueprintReadWrite, Category = "template_ue")
	FDateTime datetime;
	UPROPERTY(BlueprintReadWrite, Category = "template_ue")
	FTimespan timespan;
	UPROPERTY(BlueprintReadWrite, Category = "template_ue")
	FBox box;
	UPROPERTY(BlueprintReadWrite, Category = "template_ue")
	FMatrix mat;
	UPROPERTY(BlueprintReadWrite, Category = "template_ue")
	FTransform trans;
	UPROPERTY(BlueprintReadWrite, Category = "template_ue")
	FLinearColor lcolor;

		// 数组数据
	UPROPERTY(BlueprintReadWrite, Category = "template_ue")
	TArray<FString> strA;
	UPROPERTY(BlueprintReadWrite, Category = "template_ue")
	TArray<FName> strNA;
	UPROPERTY(BlueprintReadWrite, Category = "template_ue")
	TArray<FText> strTA;
	UPROPERTY(BlueprintReadWrite, Category = "template_ue")
	TArray<int64> i64A;
	UPROPERTY(BlueprintReadWrite, Category = "template_ue")
	TArray<int32> i32A;
	UPROPERTY(BlueprintReadWrite, Category = "template_ue")
	TArray<uint8> ui8A;
	UPROPERTY(BlueprintReadWrite, Category = "template_ue")
	TArray<FVector> vecA;
	UPROPERTY(BlueprintReadWrite, Category = "template_ue")
	TArray<FQuat> qA;
	UPROPERTY(BlueprintReadWrite, Category = "template_ue")
	TArray<FColor> colorA;
	UPROPERTY(BlueprintReadWrite, Category = "template_ue")
	TArray<FIntPoint> intpA;
	UPROPERTY(BlueprintReadWrite, Category = "template_ue")
	TArray<FVector2D> vec2dA;
	UPROPERTY(BlueprintReadWrite, Category = "template_ue")
	TArray<FRotator> rotA;
	UPROPERTY(BlueprintReadWrite, Category = "template_ue")
	TArray<FDateTime> datetimeA;
	UPROPERTY(BlueprintReadWrite, Category = "template_ue")
	TArray<FTimespan> timespanA;
	UPROPERTY(BlueprintReadWrite, Category = "template_ue")
	TArray<FBox> boxA;
	UPROPERTY(BlueprintReadWrite, Category = "template_ue")
	TArray<FMatrix> matA;
	UPROPERTY(BlueprintReadWrite, Category = "template_ue")
	TArray<FTransform> transA;
	UPROPERTY(BlueprintReadWrite, Category = "template_ue")
	TArray<FLinearColor> lcolorA;



public:
	// 实现 Serialize 函数
	virtual void Serialize(NetPacket::NetDataWriter& writer) const override
	{
		writer.Put(GetTypeHash());
			// 非数组数据
		writer.Put(str);
		writer.Put(strN);
		writer.Put(strT);
		writer.Put(i64);
		writer.Put(i32);
		writer.Put(ui8);
		writer.Put(vec);
		writer.Put(q);
		writer.Put(color);
		writer.Put(intp);
		writer.Put(vec2d);
		writer.Put(rot);
		writer.Put(datetime);
		writer.Put(timespan);
		writer.Put(box);
		writer.Put(mat);
		writer.Put(trans);
		writer.Put(lcolor);

			// 数组数据
		writer.PutArray(strA);
		writer.PutArray(strNA);
		writer.PutArray(strTA);
		writer.PutArray(i64A);
		writer.PutArray(i32A);
		writer.PutArray(ui8A);
		writer.PutArray(vecA);
		writer.PutArray(qA);
		writer.PutArray(colorA);
		writer.PutArray(intpA);
		writer.PutArray(vec2dA);
		writer.PutArray(rotA);
		writer.PutArray(datetimeA);
		writer.PutArray(timespanA);
		writer.PutArray(boxA);
		writer.PutArray(matA);
		writer.PutArray(transA);
		writer.PutArray(lcolorA);


	}

	virtual void Deserialize(NetPacket::NetDataReader& reader) override
	{
		reader.PeekUShort();
			// 非数组数据
		reader.Get(str);
		reader.Get(strN);
		reader.Get(strT);
		reader.Get(i64);
		reader.Get(i32);
		reader.Get(ui8);
		reader.Get(vec);
		reader.Get(q);
		reader.Get(color);
		reader.Get(intp);
		reader.Get(vec2d);
		reader.Get(rot);
		reader.Get(datetime);
		reader.Get(timespan);
		reader.Get(box);
		reader.Get(mat);
		reader.Get(trans);
		reader.Get(lcolor);

			// 数组数据
		reader.GetArray(strA);
		reader.GetArray(strNA);
		reader.GetArray(strTA);
		reader.GetArray(i64A);
		reader.GetArray(i32A);
		reader.GetArray(ui8A);
		reader.GetArray(vecA);
		reader.GetArray(qA);
		reader.GetArray(colorA);
		reader.GetArray(intpA);
		reader.GetArray(vec2dA);
		reader.GetArray(rotA);
		reader.GetArray(datetimeA);
		reader.GetArray(timespanA);
		reader.GetArray(boxA);
		reader.GetArray(matA);
		reader.GetArray(transA);
		reader.GetArray(lcolorA);


	}

	virtual uint16_t GetTypeHash() const override
	{
		return MurmurHash16("template_ue");
	}
};

