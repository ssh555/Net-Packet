# 构建项目
执行GenerateProjects_VS2019.bat构建，可修改bat内的参数构建指定IDE的项目
## 非UE版本
	直接构建DLL即可
## UE版本
	UE版本用UE插件的形式接入，与非UE版本最大的区别是StructFileGenerator生成的是UE中支持蓝图的结构体类型，并且只有生成的数据包结构体才能在蓝图中调用，其余均不能调用，即发送包需要单独由C++开放接口供蓝图调用，使用此版本，蓝图只能操作数据包结构体数据，不能进行序列化和反序列化等操作
	UE版本需要删除源文件中第一行包含的预编译头文件

# NetPacket
NetPacket项目为导出供其他项目使用的DLL项目

参考LiteNetLib库的数据包协议
### Packet协议
	暂定使用TCP进行网络传输，自定义的PacketHeader只需要: PacketSize(不包括PacketSize的字节数)、TypeHashID(数据类型对应的HashID)
	Packet = PacketSize(4字节) + ClientID(2字节) + TypeHashID(2字节) + 序列化字节流数据
	PacketSize =  TypeHashID(2字节) + 序列化字节流数据
	总的Packet字节数 = 6字节 + PacketSize
	PacketSize和ClientID为NetPacket前部预留的6字节数据，自动填装，TypeHashID由INetSerializable序列化时在生成代码中自动加入
#### 字符串|带长度的数组型数据
	ushort两字节字符串长度(数组数量)+实际byte数据

### 数据包管理
#### NetPacket
	数据包载体
#### NetManager.PacketPool
	数据包对象池

### Utils
#### FastBitConverter
	bit和byte处理
#### INetSerializable
	网络数据序列化和反序列化接口，用于自定义网络数据类型
#### NetDataReader
	反序列化，字节流数据读取器
#### NetDataWriter 
	序列化，字节流数据写入器
#### NetSerializableStructGenerator
	根据配置数据生成对应的实现INetSerializable接口的数据结构体C++文件(需加入UE宏支持蓝图 & 加入#if 支持非UE)
	模板文件 Default.np UE.np，生成的代码只包含头文件
	数组类型、非数组是不同的标识
#### NetSerializableStructLoader -> 使用json第三方库代替，合并到NetSerializableStructGenerator
	读入需要生成的数据结构体的配置，只是载入配置文件数据
#### ProjectBuilder.bat
	编写用于生成数据结构体文件 & 编译生成UE项目
	即运行即可生成所有文件&自动完成UE C++编译生成

### 数据包处理
#### NetPacketProcessor
	1. 网络数据包处理器，数据序列化写入(Write) & 数据反序列化读取(Read) & 接收包体时的数据处理回调，但不负责接收和发送。
	2. 包括只进行序列化和反序列化的读写(类对象内部没有任何数据) 以及 NetSerializer对数据类型进行托管，接收处理时自动序列化读取并且响应事件。
	3. 处理队列：接收包时将数据包放置于待处理队列，帧结束或者开始时统一调用Process统一处理，并在处理完之后回收所有数据包。
	4. 提供接口：Receive(Packet)接收数据包、Process()处理所有待处理队列的数据包、Serialize(INetSerializable)序列化返回数据包
#### NetSerializer -> 不再使用，与NetPacketProcessor合并
	网络数据序列化器，托管处理网络数据，对在此进行注册的数据，反序列化接收数据后进行委托事件响应处理数据包，内部也不存储任何数据，只是对数据的序列化和反序列化进行了一层处理委托事件托管包装。

# StructFileGenerator
StructFileGenerator项目为可执行的EXE项目，用于生成数据类型结构体文件
### 参数
	-i 输入目录 -o 输出目录
	不提供则默认为当前目录的./Generate

