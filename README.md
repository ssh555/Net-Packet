# NetPacket
 
�ο�LiteNetLib������ݰ�Э��
PacketЭ��
	�ݶ�ʹ��TCP�������紫�䣬�Զ����PacketHeaderֻ��Ҫ: PacketSize(������PacketSize���ֽ���)��TypeHashID(�������Ͷ�Ӧ��HashID)
	Packet = PacketSize(4�ֽ�) + TypeHashID(8�ֽ�) + ���л��ֽ�������
	PacketSize = TypeHashID(8�ֽ�) + ���л��ֽ�������
	�ܵ�Packet�ֽ��� = 4�ֽ� + PacketSize

���ݰ�����
	NetPacket -> ���ݰ�����
	NetManager.PacketPool -> ���ݰ������

Utils
	FastBitConverter -> BIT����
	INetSerializable -> �����������л��ͷ����л��ӿڣ������Զ���������������
	NetDataReader -> �����л����ֽ������ݶ�ȡ��
	NetDataWriter -> ���л����ֽ�������д����
	NetSerializableStructGenerator -> ���������������ɶ�Ӧ��ʵ��INetSerializable�ӿڵ����ݽṹ��C++�ļ�(�����UE��֧����ͼ & ����#if ֧�ַ�UE)
	NetSerializableStructLoader -> ������Ҫ���ɵ����ݽṹ�������
	ProjectBuilder.bat -> ��д�����������ݽṹ���ļ� & ��������UE��Ŀ�������м������������ļ�&�Զ����UE C++��������

���ݰ�����
	NetPacketProcessor -> �������ݰ����������������л�д��(Write) & ���ݷ����л���ȡ(Read) & ���հ���ʱ�����ݴ���ص�������������պͷ��͡�����ֻ�������л��ͷ����л��Ķ�д(������ڲ�û���κ�����) �Լ� NetSerializer���������ͽ����йܣ����մ���ʱ�Զ����л���ȡ������Ӧ�¼�
	NetSerializer -> �����������л������йܴ����������ݣ����ڴ˽���ע������ݣ������л��������ݺ����ί���¼���Ӧ�������ݰ����ڲ�Ҳ���洢�κ����ݣ�ֻ�Ƕ����ݵ����л��ͷ����л�������һ�㴦��ί���¼��йܰ�װ��

NetPacket��ĿΪ������������Ŀʹ�õ�DLL��Ŀ
StructFileGenerator��ĿΪ��ִ�е�EXE��Ŀ�����������������ͽṹ���ļ������ṩ����
	-i ����Ŀ¼ -o ���Ŀ¼
	���ṩ��Ĭ��Ϊ��ǰĿ¼��./Generate

