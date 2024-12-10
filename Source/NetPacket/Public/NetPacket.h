#if NP_UE_SUPPORT
// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FNetPacketModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

#endif

namespace NetPacket
{
	class NetDataReader;
	class NetDataWriter;

	class NetPackage {
		// ��Ӷ���ص���Ԫ
		friend class NetPacketPool;
	public:
		static const int32_t MaxPacketSize;

	private:
		// �������ݰ���С
		NetPackage(uint32_t maxSize = 1024);
		~NetPackage();

		NetPackage* Next;
		NetPacketPool* pool;
		void resize(int32_t size);

	public:
		// �������ݰ�����Ҫ���� m_size �ضϣ�ֱ���������ͣ����������˽��յ�ʱ��Ҳ����Ϊ���ݰ��ڴ滺��Ҳ�п����˷�
		const uint8_t* getRawData() const;
		// ���ݰ���С
		int32_t getSize() const;
		int32_t getMaxSize() const;
		// �����ݿ��������ݰ����ڴ�
		void setRawData(const uint8_t* data, const int32_t size);
		// �����ݿ��������ݰ����ڴ�
		void setData(NetDataWriter* writer);

		// reader��ȡ���ݺ�ص�����أ��������ɹ��������ڴ棬�辡�촦��
		void GetData(NetDataReader* reader);


	private:
		// �����ݣ���������δʹ�õĿռ�
		uint8_t* RawData;
		// ��ǰռ�õĴ�С
		int32_t m_size;
		// �������
		int32_t MaxSize;
	};
}