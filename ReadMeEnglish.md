# NetPacket
- Packet Protocol Library: Used for reading, writing, and processing byte stream data in networks, with support for custom packet types.
- Code Generation: Automatically generates corresponding struct code for configured packets.
- Supports C++ and UE C++ & Blueprints.

# Building the Project
Execute `GenerateProjects_VS2019.bat` to build the project. You can modify the parameters inside the `.bat` file to build the project for a specific IDE.

## Non-UE Version
Directly build the DLL.

## UE Version
The UE version is integrated as a UE plugin. The main difference from the non-UE version is that the `StructFileGenerator` generates struct types supported by UE Blueprints. Only the generated packet structs can be called in Blueprints; the rest cannot. This means that sending packets requires a separate C++ interface to be exposed for Blueprint calls. In this version, Blueprints can only manipulate packet struct data and cannot perform serialization or deserialization operations.

For the UE version, the first line of the source file containing the precompiled header must be removed.

# NetPacket
The NetPacket project is a DLL project exported for use by other projects.

Referencing the packet protocol of the LiteNetLib library.

### Packet Protocol
TCP is tentatively used for network transmission. The custom `PacketHeader` only requires: `PacketSize` (excluding the byte count of `PacketSize`) and `TypeHashID` (the HashID corresponding to the data type).

```
Packet = PacketSize (4 bytes) + ClientID (2 bytes) + TypeHashID (2 bytes) + serialized byte stream data
PacketSize = TypeHashID (2 bytes) + serialized byte stream data
Total Packet byte count = 6 bytes + PacketSize
```

`PacketSize` and `ClientID` are the first 6 bytes of data reserved in `NetPacket`, automatically filled. `TypeHashID` is automatically added during serialization by `INetSerializable` in the generated code.

#### Strings | Arrays with Length
`ushort` (2 bytes) string length (array count) + actual byte data.

### Packet Management
#### NetPacket
The packet carrier.

#### NetManager.PacketPool
Packet object pool.

### Utils
#### FastBitConverter
Bit and byte processing.

#### INetSerializable
Network data serialization and deserialization interface for custom network data types.

#### NetDataReader
Deserialization, byte stream data reader.

#### NetDataWriter
Serialization, byte stream data writer.

#### NetSerializableStructGenerator
Generates corresponding C++ files for data structures implementing the `INetSerializable` interface based on configuration data (requires UE macro support for Blueprints & `#if` support for non-UE).

Template files: `Default.np`, `UE.np`. The generated code only includes header files.

Array types and non-array types have different identifiers.

#### NetSerializableStructLoader -> Replaced with a third-party JSON library, merged into `NetSerializableStructGenerator`.
Loads configuration data for generating data structures, only loading configuration file data.

#### ProjectBuilder.bat
Script for generating data structure files & compiling UE projects. Running it will generate all files & automatically complete UE C++ compilation.

### Packet Processing
#### NetPacketProcessor
1. Network packet processor, responsible for data serialization (Write) & deserialization (Read) & data processing callbacks when receiving packets, but not responsible for receiving and sending.
2. Includes read/write operations that only perform serialization and deserialization (no data inside the class object) and `NetSerializer` hosting data types, automatically serializing and reading data upon reception and responding to events.
3. Processing queue: Places received packets in a pending queue, processes them all at the end or start of a frame, and recycles all packets after processing.
4. Provides interfaces: `Receive(Packet)` to receive packets, `Process()` to process all packets in the pending queue, and `Serialize(INetSerializable)` to serialize and return packets.

#### NetSerializer -> No longer used, merged into `NetPacketProcessor`.
Network data serializer, hosting network data processing. For data registered here, deserializes received data and delegates event responses for packet processing. It does not store any data internally, only wrapping serialization and deserialization with a layer of delegated event hosting.

# StructFileGenerator
The `StructFileGenerator` project is an executable EXE project used to generate data type structure files.

### Parameters
`-i` input directory, `-o` output directory. If not provided, defaults to `./Generate` in the current directory.

# Usage Examples
### NetPacketProcessor Network Packet Entry
- Receives packets.
- Processes packets.
- Registers callback delegates for automatic data type processing.
- Does not support UE types, not `UClass`, cannot be called by Blueprints.
- It is recommended to have a globally accessible method for `NetPacketProcessor`.
- [Packet Protocol](#packet-protocol)

```C++
// Packet processor
NetPacket::NetPacketProcessor processor;
// Serialization
NetPacket::NetDataWriter writer;
// Deserialization
NetPacket::NetDataReader reader;

// Register callback event
// Replace Ftemplate_ue with your data type
// Delegate is FRegisterProcessDelegate
// Can directly use std::function<void(int16_t, INetSerializable*)> <clientID, actual data pointer>
processor.Register<Ftemplate_ue>(Ftemplate_ue::GetTypeHash(), NetPacket::NPFunctionLibrary::WrapDelegate(Delegate));

// Serialize data
t.Serialize(writer);
reader.SetSource(writer.CopyData(), writer.Length());
// Deserialize data
r.Deserialize(reader);
delete[] reader.GetRawData();

// Receive network data - do not process to avoid blocking the receiving thread
// If data does not contain packetsize and clientid, use the last parameter false. If it does, use true (default parameter).
// See packet protocol section
processor.Receive(const_cast<uint8_t*>(writer.Data()), writer.Length(), false);

// Process all previously received packets
processor.Process();
```

### FRegisterProcessDelegate
- UE-wrapped delegate callback.
```C++
DECLARE_DYNAMIC_DELEGATE_TwoParams(FRegisterProcessDelegate, int32, clienID, UNPStructRef*, data);
```

### NetPacket::NPFunctionLibrary::WrapDelegate
- Used to wrap UE delegates, returning a delegate callback that can be directly used in `NetPacketProcessor.Register`.
- Can be encapsulated for Blueprint calls.
```C++
// Can wrap a function for Blueprint calls like below
UFUNCTION(BlueprintCallable, Category = "Gameplay")
static void TestNPDelegate(UStruct* stype, FRegisterProcessDelegate Delegate);

void USGameplayFunctionLibrary::TestNPDelegate(UStruct* stype, FRegisterProcessDelegate Delegate)
{
	// Call in Blueprint
	// 1. Use UNPBPFunctionLibrary::GetUStructPtr to get the struct type object or use UNPBPFunctionLibrary::GetUStructPtr_template_ue to directly get it without needing a corresponding object (replace template_ue with your custom data type).
	// 2. Pass the type object and delegate to your encapsulated function (similar to this function) for registration.

	// Need to get your own processor (not supported in Blueprint types)
	UNPBPFunctionLibrary::Register(processor, stype, Delegate);
}
```

### UNPBPFunctionLibrary
- Code is automatically generated and will include functions corresponding to your custom data types.
- Used for UE Blueprint or C++ calls.
- Called in `FRegisterProcessDelegate` to parse the actual data struct object from `*UNPStructRef*`.
```C++
UCLASS()
class NP_API UNPBPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	// Create a Ref, can be used with ConvertToDummyStruct to store data in Ref
	UFUNCTION(BlueprintCallable, Category = "NPCast")
	static UNPStructRef* CreateRef()
	{
		return NewObject<UNPStructRef>();
	}

	// Code automatically generates GetUStructPtr for corresponding types
	UFUNCTION(BlueprintCallable, Category = "NPCast")
	static UStruct* GetUStructPtr(const Ftemplate_ue& obj)
	{
		return obj.StaticStruct();
	}

	UFUNCTION(BlueprintCallable, Category = "NPCast")
	static UStruct* GetUStructPtr_template_ue()
	{
		return Ftemplate_ue::StaticStruct();
	}

	// Code automatically generates ConvertTotemplate_ue for corresponding types
	UFUNCTION(BlueprintCallable, Category = "NPCast")
	static void ConvertTotemplate_ue(const UNPStructRef* Parent, Ftemplate_ue& data)
	{
		data = *static_cast<Ftemplate_ue*>(Parent->obj);
	}

	// Code automatically generates conversion to base struct type
	UFUNCTION(BlueprintCallable, Category = "NPCast")
	static const FDummyStruct& ConvertToDummyStruct(const Ftemplate_ue& data)
	{
		return static_cast<const FDummyStruct&>(data);
	}

	static void Register(NetPacket::NetPacketProcessor& processor, UStruct* structType, FRegisterProcessDelegate Delegate)
	{
		if (structType == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("UStruct cannot be nullptr!"));
			return;
		}
		// Code automatically generates registration for corresponding types
		else if (structType == Ftemplate_ue::StaticStruct())
		{
			processor.Register<Ftemplate_ue>(Ftemplate_ue::GetTypeHash(), NetPacket::NPFunctionLibrary::WrapDelegate(Delegate));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Unknown struct type!"));
		}
	}
};
```

### Data Type Configuration and Usage
[Configuration File Code Generation](./ConfigurationFileCodeGeneration.md ':include')
