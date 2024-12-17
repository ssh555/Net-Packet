#pragma once
#include "../nppch.h"
// 如果报错，修改include为你自己的正确路径
#include "../INetSerializable.h"
#include "../NetDataWriter.h"
#include "../NetDataReader.h"
// 需包含自定义数据类型的头文件
#include "example.hpp"


namespace NetPacket
{
	class templateA : public INetSerializable
	{
	public:
		// 非数组数据
		uint8_t ui8;
		int8_t i8;
		bool b;
		int16_t i16;
		uint16_t ui16;
		int32_t i32;
		uint32_t ui32;
		int64_t i64;
		uint64_t ui64;
		float f;
		double d;
		std::string str;
		Test test;
		char ch;
		std::byte bt;

		// 数组数据
		uint8_t ui8a[5];
		int8_t i8a[5];
		bool ba[5];
		int16_t i16a[5];
		uint16_t ui16a[5];
		int32_t i32a[5];
		uint32_t ui32a[5];
		int64_t i64a[5];
		uint64_t ui64a[5];
		float fa[5];
		double da[5];
		std::string stra[5];
		Test testa[5];
		char cha[5];
		std::byte bta[5];



	public:
		virtual void Serialize(NetDataWriter& writer) const override
		{
			writer.Put(GetTypeHash());
			// 非数组数据
			writer.Put(ui8);
			writer.Put(i8);
			writer.Put(b);
			writer.Put(i16);
			writer.Put(ui16);
			writer.Put(i32);
			writer.Put(ui32);
			writer.Put(i64);
			writer.Put(ui64);
			writer.Put(f);
			writer.Put(d);
			writer.Put(str);
			writer.Put(test);
			writer.Put(ch);
			writer.Put(bt);

			// 数组数据
			writer.PutArray(ui8a, 5);
			writer.PutArray(i8a, 5);
			writer.PutArray(ba, 5);
			writer.PutArray(i16a, 5);
			writer.PutArray(ui16a, 5);
			writer.PutArray(i32a, 5);
			writer.PutArray(ui32a, 5);
			writer.PutArray(i64a, 5);
			writer.PutArray(ui64a, 5);
			writer.PutArray(fa, 5);
			writer.PutArray(da, 5);
			writer.PutArray(stra, 5);
			writer.PutArray(testa, 5);
			writer.PutArray(cha, 5);
			writer.PutArray(bta, 5);


		}

		virtual void Deserialize(NetDataReader& reader) override
		{
			reader.PeekUShort();
			// 非数组数据
			reader.Get(ui8);
			reader.Get(i8);
			reader.Get(b);
			reader.Get(i16);
			reader.Get(ui16);
			reader.Get(i32);
			reader.Get(ui32);
			reader.Get(i64);
			reader.Get(ui64);
			reader.Get(f);
			reader.Get(d);
			reader.Get(str);
			reader.Get(test);
			reader.Get(ch);
			reader.Get(bt);

			// 数组数据
			reader.GetArray(ui8a);
			reader.GetArray(i8a);
			reader.GetArray(ba);
			reader.GetArray(i16a);
			reader.GetArray(ui16a);
			reader.GetArray(i32a);
			reader.GetArray(ui32a);
			reader.GetArray(i64a);
			reader.GetArray(ui64a);
			reader.GetArray(fa);
			reader.GetArray(da);
			reader.GetArray(stra);
			reader.GetArray(testa);
			reader.GetArray(cha);
			reader.GetArray(bta);


		}

		static uint16_t GetTypeHash()
		{
			return MurmurHash16("templateA");
		}
	};
}
