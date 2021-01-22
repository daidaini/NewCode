#ifndef __DataDef__HQ__H__JDKAOPUHNGFJKSGHUIERO784__
#define __DataDef__HQ__H__JDKAOPUHNGFJKSGHUIERO784__


//#ifdef _WINDOWS
#define MAX(A,B)	((A)>(B)?(A):(B))
#define MIN(A,B)	((A)<(B)?(A):(B))
//#endif

#define			MAX_MOBILE_PACKAGE_SIZE_STEP			(65535-100)
#define			MAX_MOBILE_PACKAGE_BUFFER_SIZE_STEP		(65535+200)

#define			MAX_MOBILE_PACKAGE_SIZE			4096
#define			MAX_MOBILE_PACKAGE_BUFFER_SIZE	6000

#define			CONST_E							(2.71828182845904523536028)

//�ֽڶ���
#if defined(WIN32) || defined(__WIN32__) || defined(__WIN32) || defined(__WINS__)
#pragma pack(1)
#define PACKED
#else
#define PACKED __attribute__((packed, aligned(1)))
#endif


typedef struct
{
	BYTE                           zip:2;			//0��ʾδѹ����1��ʾzlibѹ��
	BYTE                           unused:6;        //δʹ��
	UINT16						   zipdatasize;     //����ѹ����ĳ���
}PACKED PB_ZipHead;   //3byte

typedef struct
{
	BYTE							sign;			//Э���ʶ��Ŀǰ����Ϊ66
	BYTE							crypt:2;		//0��ʾδ���ܣ�1��ʾ���ݼ�����
	BYTE							unused:6;		//δʹ��
	BYTE							PackageNum;		//ͨѶ������
	BYTE							PackageNo;		//��ǰͨѶ����ţ���0��ʼ����ΪPackageNum-1ʱ��ʾ�����һ��ͨѶ��
	UINT16							CheckCode;		//У���루��ͨѶ�������CRC16У�飬�ڼ���ѹ����
	UINT16							PackageSize;	//����ĳ��ȣ�����ѹ����
}PACKED PB_FrameHead;	//8byte

typedef struct
{
	UINT32							ComHead_Len;
}PACKED PB_ComHead;
typedef struct
{
	unsigned short							PackageSize;	//�����С
	unsigned char							ZipFlag;		//0��ʾδѹ����1��ʾzlibѹ��
} PACKED MC_FrameHead;	//16byte
#pragma pack()

#endif
