#pragma once
#include "nppch.h"
#include "NetSerializableStructGenerator.h"

namespace NetPacket
{
	const std::string NetStructConfig::DefaultConfig = R"(
#pragma once
#include "nppch.h"
#include "INetSerializable.h"
#include "NetDataWriter.h"
#include "NetDataReader.h"

namespace NetPacket
{
	class {CLASSNAME} : public INetSerializable
	{
	public:
{DECLATEDATA}

	public:
		virtual void Serialize(NetDataWriter& writer) const override
		{
			writer.Put(GetTypeHash());
{WRITERDATA}
		}

		virtual void Deserialize(NetDataReader& reader) override
		{
			reader.PeekUShort();
{READRDATA}
		}
	};
}
)";

}