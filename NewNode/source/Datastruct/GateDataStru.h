#ifndef DataLH
#define DataLH
//#include <Afxtempl.h>
//baimh,20060731，如果编译时不带mfc，则有Afxtempl.h会编译报错
//TCHAR.h：_T
//stdio.h:sprintf

#include "platform.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <wsipx.h>
#include "LogInterface.h"
#include "MLmyUnit.hpp"
#include "DataDef_HQ.h"
#include "STD.h"

#define	LISTTYPE_USERINFO		1		//用户列表信息
#define	LISTTYPE_ADDRESSINFO	2		//后台地址列表信息
#define LISTTYPE_GET_NUM		100
#define	LISTTYPE_PAGE_1			101
#define	LISTTYPE_PAGE_2			102
#define	LISTTYPE_PAGE_3			103
#define	LISTTYPE_PAGE_4			104
#define	LISTTYPE_PAGE_5			105
#define	LISTTYPE_PAGE_6			106
#define	LISTTYPE_PAGE_7			107
#define	LISTTYPE_PAGE_8			108
#define	LISTTYPE_PAGE_9			109
#define LISTTYPE_GET_ACCOUNT_NUM 110  //查询网关登录上各个平台的用户数据

#define	DRAWALL					0		//显示所有
#define	DRAWUPDATE				1		//更新记录信息

#define	MAX_ROUTE_ADDRESS_NUM	64		//最大后台路由信息
#define	MAX_SAME_ADDRESS_NUM	5		//相同路由时的最大地址数

enum InfoType
{
	CI_UPDATECOUNT,
	CI_ADDINFO,
	CI_UPDATEINFO,
	CI_DELINFO,
	CI_CONN,			//连接成功
	CI_NOTCONN,			//连接失败
};

enum OPERATION_RESULT // 操作完成结果
{
	//OR_CURRENT_LIMMIT_ERROR = -10,	//限流错误，针对CTP，表示每秒限流或者未处理请求过多
	OR_ACCORPWD_ERROR	= -9,	//账号或者密码错误
	
	OR_UNLOGIN_ERROR	= -8,	//未登录 （博易6处理）
	OR_LOGIN_EXIT     = -7,		//重复登录，账户被踢
	OR_FUNCTIME_ERROR = -6,		//	流量控制，禁止频繁发送同一个请求
	OR_TYPE_ERROR   = -5,		//	不支持的登录类别错误
	OR_NOFUNC_ERROR = -4,		//	没有实现的功能
	OR_CONNECT_FAIL = -3,		//	与后台连接失败
	OR_NET_ERROR = -2,			//	网络连接断开或传输失败，本次数据请求操作将不得不终止，将断开客户端和国泰的连接
	OR_ERRMSG_ERROR = -1,		//	操作成功，返回结果错误号小于零，有错误解释返回。或者客户端是非法用户
	OR_NOREC_ERROR = 0,			//	没有结果返回。产生可能为后台无此功能。(用于金证，当发请求返回－4，取请求结果返回0)
	OR_SUCCESS = 1,
	OR_ELIGCHECK_ERROR	= -99,		//客户适当性不满足  老错误号，废弃
	OR_NO_TRADING_TIME	 = -98,		//不在交易时间
									//类CTP根据回报处理，返回错误
									//恒生（升级过不在交易时间的恒生）、金仕达、顶点直接报类似”不在交易时间”错误消息

	OR_RISKMISSMATCH_ERROR = -100,	//客户适当性不匹配  （需要签署越级协议）
	OR_PASSWORDKEY_EXPIRE = -101	//密码串过期失效
};


enum QAT_CODE{							//定义需要设置或获取的类别
	//QAT_ERRCODE			= 0,			//错误代码
	QAT_ERRMSG			= 1,			//错误信息
	QAT_DEPARTCODE		= 2,			//营业部代码
	QAT_CONNSTATE		= 3,			//连接状态，值为0或1,1表示连接
	QAT_ACCOUNT			= 4,			//帐号|平台信息|客户端版本号|
										
	QAT_CONFIG			= 5,			//主要是配置的地址及信息等	SiteInfo
	QAT_DLLINFO			= 6,			//业务模块的信息	tagDLLVer
	QAT_NETADDR			= 7,			//本机网络地址
	QAT_USETIME			= 8,			//获取到期日期，为long型，如果不支持时返回QAT_RET_NOT,则主程序忽略
										//返回QAT_RET_FAIL时，需要查看返回的data，分别为-2,-1,0及正确的年月日
	QAT_USERINFO		= 9,			//连接用户信息，主程序使用本接口传递用户信息给业务模块，比如
										//m_nSerno,m_nClientSocket,传输的结构体是tagQATUserInfo
	QAT_HQDLLINFO		= 10,			//行情模块信息		tagDLLVer

	//QAT_MAIN_FUNC_PTR	= 11,			//用于将主程序的一些标准函数指针传递给下一层(tagMainFuncPtr)
};

enum QAT_RET_CODE {						//定义以下两函数的返回值
	QAT_RET_MEMSIZE_ERROR	= 1,		//给定的内存太小，新的大小在len中指定，但还是拷贝到指定大小的数据
	QAT_RET_SUCCESS			= 0,		//成功
	QAT_RET_FAIL			= -1,		//失败
	QAT_RET_NOT				= -2		//不支持的代码
};

//定义协议类别，一种协议占用一个位
enum COMM_TYPE
{
	CT_UNKOWN			= 0,
	CT_OLDTYPE			= 1,	//老协议
	CT_STEPTYPE			= 2,		//新协议
	CT_STEPTYPE_AES		= 3     //STEP协议 使用AES加密
};

#pragma pack(1)
struct ConInfo
{
	time_t MaxUserTime;			//后台最大连接数的时间
	long MaxUser;				//最大用户数
	long CurUser;				//最大用户数
};
struct OneSite
{
	UINT port;				//后台端口号
	char IP[20];				//后台IP地址
	BYTE szStat;				//状态， 0x00未检测  0x01连接上 0x02 断开	0x03 连接中
	ConInfo UserInfo;			//用户连接信息
	char szRemark[30];		//文字描述
	BYTE bConnectFlag;		//与后台的状态，表示经检测成功率后的状态，0为不支持，1为正常，2为异常,20070202添加三项,baimh
	char LogPara[256];		//连接参数
};

//站点内容
struct SiteInfo
{
	long nAddressCount;		//地址数量
	OneSite Address[32];		//地址信息
};

struct tagDLLVer
{
	char m_szSign[10];		// dll标识，固定为QLDLL，区分大小写
	char m_szIdentify[20];	// 版本标识，标识柜台厂商版本，"KD25,KD32"
	long m_lUpdateDate;		// 更新日期，dll更新日期
	union DLL_VERSION	
	{
		long l;
		struct {
			unsigned short ver;		// 如3.1-->31
			unsigned short build;	// 内部号3位:001
		}w;
	}m_Ver;				// dll版本

	char m_szDescription[512];
	int	m_DllType[10];		//可送多个，碰到最后一个或者值为-1表示没有了
								//DLL的类别，同委托协议里定义的“登录类别”
								//0:普通沪深交易
								//5:融资融券交易
								//6:个股期权交易
	COMM_TYPE m_CommType;		//本值表示业务模块支持的协议种类，通讯模块使用本值来判断业务模块支持的协议类别
	char m_DllType_Com[10];  //Com配置交易模块支持的类型    Com没有配置 默认交易模块自己定义的
} ;					//用于业务动态库信息

struct tagQATUserInfo
{
	int	m_nSerno;			// 用户数组序号
	int	m_nUserID;			// 用户唯一ID号
	SOCKET m_nClientSocket;	// 存储客户端socket
};	//传输QAT_USERINFO信息时的结构体

struct LIST_HEAD
{
	long size;
	long type;
	long flag;
	long recordnum;
	long fieldnum;
	char title[80];
};

//用户登录信息统计
struct UserLogStat
{
	long MaxUser_MI; //IOS手机用户最大在线数
	long CurUser_MI; //IOS手机用户当前在线数
	long MaxUser_MA; //安卓手机用户最大在线数
	long CurUser_MA; //安卓手机用户当前在线数 
	long MaxUser_PC; //PC用户最大在线数
	long CurUser_PC; //PC户当前在线数
};

struct VerHead
{
	char head[16];		//pengbo
	int	version;		//0--不加密，1--加密
	int	fileLen;		//文件内容长度
};

struct MTC_FieldInfo
{
 	int fieldno;
	char fieldname[64];
};

struct tagKeyFileHead
{
	unsigned short checkcode;	//除本两字节以外的所有数据
	char sign[8];			//PTTA0002
};

//第二代
struct tagKeyData	//共96字节
{	
	unsigned short checkcode;
	INT32 ver;					//0
	INT32 updatetime;
	char AuthCode[65];			//认证码
	char unused[21];				//未用部分
};

#pragma pack()

#endif
