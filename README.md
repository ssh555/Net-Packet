# ������Ŀ
ִ��GenerateProjects_VS2019.bat���������޸�bat�ڵĲ�������ָ��IDE����Ŀ
## ��UE�汾
	ֱ�ӹ���DLL����
## UE�汾
	UE�汾��UE�������ʽ���룬���UE�汾����������StructFileGenerator���ɵ���UE��֧����ͼ�Ľṹ�����ͣ�����ֻ�����ɵ����ݰ��ṹ���������ͼ�е��ã���������ܵ��ã������Ͱ���Ҫ������C++���Žӿڹ���ͼ���ã�ʹ�ô˰汾����ͼֻ�ܲ������ݰ��ṹ�����ݣ����ܽ������л��ͷ����л��Ȳ���

# NetPacket
NetPacket��ĿΪ������������Ŀʹ�õ�DLL��Ŀ

�ο�LiteNetLib������ݰ�Э��
### PacketЭ��
	�ݶ�ʹ��TCP�������紫�䣬�Զ����PacketHeaderֻ��Ҫ: PacketSize(������PacketSize���ֽ���)��TypeHashID(�������Ͷ�Ӧ��HashID)
	Packet = PacketSize(4�ֽ�) + ClientID(2�ֽ�) + TypeHashID(2�ֽ�) + ���л��ֽ�������
	PacketSize =  TypeHashID(2�ֽ�) + ���л��ֽ�������
	�ܵ�Packet�ֽ��� = 6�ֽ� + PacketSize
	PacketSize��ClientIDΪNetPacketǰ��Ԥ����6�ֽ����ݣ��Զ���װ��TypeHashID��INetSerializable���л�ʱ�����ɴ������Զ�����
#### �ַ���|�����ȵ�����������
	ushort���ֽ��ַ�������(��������)+ʵ��byte����

### ���ݰ�����
#### NetPacket
	���ݰ�����
#### NetManager.PacketPool
	���ݰ������

### Utils
#### FastBitConverter
	bit��byte����
#### INetSerializable
	�����������л��ͷ����л��ӿڣ������Զ���������������
#### NetDataReader
	�����л����ֽ������ݶ�ȡ��
#### NetDataWriter 
	���л����ֽ�������д����
#### NetSerializableStructGenerator
	���������������ɶ�Ӧ��ʵ��INetSerializable�ӿڵ����ݽṹ��C++�ļ�(�����UE��֧����ͼ & ����#if ֧�ַ�UE)
	ģ���ļ� Default.np UE.np�����ɵĴ���ֻ����ͷ�ļ�
#### NetSerializableStructLoader -> ʹ��json����������棬�ϲ���NetSerializableStructGenerator
	������Ҫ���ɵ����ݽṹ������ã�ֻ�����������ļ�����
#### ProjectBuilder.bat
	��д�����������ݽṹ���ļ� & ��������UE��Ŀ
	�����м������������ļ�&�Զ����UE C++��������

### ���ݰ�����
#### NetPacketProcessor
	1. �������ݰ����������������л�д��(Write) & ���ݷ����л���ȡ(Read) & ���հ���ʱ�����ݴ���ص�������������պͷ��͡�
	2. ����ֻ�������л��ͷ����л��Ķ�д(������ڲ�û���κ�����) �Լ� NetSerializer���������ͽ����йܣ����մ���ʱ�Զ����л���ȡ������Ӧ�¼���
	3. ������У����հ�ʱ�����ݰ������ڴ�������У�֡�������߿�ʼʱͳһ����Processͳһ�������ڴ�����֮������������ݰ���
	4. �ṩ�ӿڣ�Receive(Packet)�������ݰ���Process()�������д�������е����ݰ���Serialize(INetSerializable)���л��������ݰ�
#### NetSerializer -> ����ʹ�ã���NetPacketProcessor�ϲ�
	�����������л������йܴ����������ݣ����ڴ˽���ע������ݣ������л��������ݺ����ί���¼���Ӧ�������ݰ����ڲ�Ҳ���洢�κ����ݣ�ֻ�Ƕ����ݵ����л��ͷ����л�������һ�㴦��ί���¼��йܰ�װ��

# StructFileGenerator
StructFileGenerator��ĿΪ��ִ�е�EXE��Ŀ�����������������ͽṹ���ļ�
### ����
	-i ����Ŀ¼ -o ���Ŀ¼
	���ṩ��Ĭ��Ϊ��ǰĿ¼��./Generate

