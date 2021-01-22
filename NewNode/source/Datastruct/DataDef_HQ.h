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

//字节对齐
#if defined(WIN32) || defined(__WIN32__) || defined(__WIN32) || defined(__WINS__)
#pragma pack(1)
#define PACKED
#else
#define PACKED __attribute__((packed, aligned(1)))
#endif


typedef struct
{
	BYTE                           zip:2;			//0表示未压缩，1表示zlib压缩
	BYTE                           unused:6;        //未使用
	UINT16						   zipdatasize;     //数据压缩后的长度
}PACKED PB_ZipHead;   //3byte

typedef struct
{
	BYTE							sign;			//协议标识，目前定义为66
	BYTE							crypt:2;		//0表示未加密，1表示数据加密了
	BYTE							unused:6;		//未使用
	BYTE							PackageNum;		//通讯包总数
	BYTE							PackageNo;		//当前通讯包序号，从0开始，当为PackageNum-1时表示是最后一个通讯包
	UINT16							CheckCode;		//校验码（对通讯包体进行CRC16校验，在加密压缩后）
	UINT16							PackageSize;	//包体的长度，加密压缩后
}PACKED PB_FrameHead;	//8byte

typedef struct
{
	UINT32							ComHead_Len;
}PACKED PB_ComHead;
typedef struct
{
	unsigned short							PackageSize;	//包体大小
	unsigned char							ZipFlag;		//0表示未压缩，1表示zlib压缩
} PACKED MC_FrameHead;	//16byte
#pragma pack()

#endif
