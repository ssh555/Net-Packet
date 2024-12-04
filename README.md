# NetPacket
 
参考LiteNetLib库的数据包协议
Packet协议
	暂定使用TCP进行网络传输，自定义的PacketHeader只需要: PacketSize(不包括PacketSize的字节数)、TypeHashID(数据类型对应的HashID)
	Packet = PacketSize(4字节) + TypeHashID(8字节) + 序列化字节流数据
	PacketSize = TypeHashID(8字节) + 序列化字节流数据
	总的Packet字节数 = 4字节 + PacketSize

数据包管理
	NetPacket -> 数据包载体
	NetManager.PacketPool -> 数据包对象池

Utils
	FastBitConverter -> BIT处理
	INetSerializable -> 网络数据序列化和反序列化接口，用于自定义网络数据类型
	NetDataReader -> 反序列化，字节流数据读取器
	NetDataWriter -> 序列化，字节流数据写入器
	NetSerializableStructGenerator -> 根据配置数据生成对应的实现INetSerializable接口的数据结构体C++文件(需加入UE宏支持蓝图 & 加入#if 支持非UE)
	NetSerializableStructLoader -> 读入需要生成的数据结构体的配置
	ProjectBuilder.bat -> 编写用于生成数据结构体文件 & 编译生成UE项目，即运行即可生成所有文件&自动完成UE C++编译生成

数据包处理
	NetPacketProcessor -> 网络数据包处理器，数据序列化写入(Write) & 数据反序列化读取(Read) & 接收包体时的数据处理回调，但不负责接收和发送。包括只进行序列化和反序列化的读写(类对象内部没有任何数据) 以及 NetSerializer对数据类型进行托管，接收处理时自动序列化读取并且响应事件
	NetSerializer -> 网络数据序列化器，托管处理网络数据，对在此进行注册的数据，反序列化接收数据后进行委托事件响应处理数据包，内部也不存储任何数据，只是对数据的序列化和反序列化进行了一层处理委托事件托管包装。

NetPacket项目为导出供其他项目使用的DLL项目
StructFileGenerator项目为可执行的EXE项目，用于生成数据类型结构体文件，需提供参数
	-i 输入目录 -o 输出目录
	不提供则默认为当前目录的./Generate

