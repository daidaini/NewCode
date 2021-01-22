#ifndef	__PB_API_H__
#define __PB_API_H__

#define	MAX_USER_NUM		65536	// 支持最大用户

	typedef struct {
		long	serno;
		long	userid;
		SOCKET	s_client;
		char	unused[100];
	} tagUserInfo;

	typedef struct {
		long	serno;
		long	userid;
		void*	pInterface;
		char*	request;		//请求数据
		int		requestsize;	//请求大小
	} tagRequestIn;

	typedef struct {
		int		checkcode;		//返回信息，0表示不是完整包，>0表示已处理多个请求，负数表示错误，可关闭用户
		int		packagesize;	//已处理请求大小

		char*	out;			//返回应答数据指针
		int		outlen;			//返回应答数据大小
		//int		errorcode;
	} tagRequestOut;

#pragma pack(1)
	typedef struct {
		char		username[32];
		char		pwd[16];
		INT32		fwbm;					//服务器编码	22	INT32
		char		fwmc[32];				//服务器名称	23	WCHAR(32)
		INT32		currusernum;			//当前用户数	24	INT32
		__int32		maxusernum;				//最大用户数	25	INT32
		char		maxusertime[32];		//最大用户数发生时间	26	CHAR(19) Yyyy-mm-dd hh:mm:ss
		char		servicetime[32];		//服务器时间	27	CHAR(19)
		INT32		status;					//工作状态	28	INT80:异常；1：正常 30字段可指明异常原因
		char		statusname[8];			//状态名称	29	WCHAR(10)
		char		remark[512];			//备注	30	WCHAR(1024)
		char		worktime[32];			//启动后的工作时间	31	CHAR(20) D-hh:mm:ss：表示工作了多少天及时分秒
		char		cpurate[16];			//CPU使用率	32	CHAR(10)
		char		memoryrate[16];			//内存使用率	33	CHAR(10)
		int			SendBytesPerSecond;		//每秒流量
		int			maxSendBytesPerSecond;	//最大每秒流量
		char		Version[128];			//业务模块版本
		int			MaxUsrNum;				//配置的最大连接用户数
		char		DumpTime[64];			//崩溃时间
		int			CPUCount;				//CPU数量
		int			TotalPhyMemory;			//物理内存大小（单位：G）
		double		CPUFreq;				//主频 单位G
	}tagServiceInfo;
#pragma pack()
	
	typedef bool	(* __GetServiceInfo)(tagServiceInfo* info, int size);
	typedef void*	(* __MemoryManage_Alloc)(int& NeedSizeAndRealSize);
	typedef bool	(* __MemoryManage_Push)(void* mem);

	typedef struct {
		__GetServiceInfo			pgetServiceInfo;	//获取服务器信息
	} tagMainFuncPtr;

	#define PB_API extern "C"  __declspec(dllexport)

	// 动态库初始化函数，
	// pszConfigFile:配置文件名
	// 返回错误号，0成功，负数失败
	PB_API	int		UserDll_Init(const char* pszConfigFile);
	PB_API	int		UserDll_Init_Path(const char* pszConfigFile,const char*);
	PB_API	int		UserDll_Release();			// 动态库释放函数

	// 以下所有请求返回0时表示成功，负数表示失败
	PB_API	void*	UserDll_CreateUser(long serno, long userid);		// 创建用户
	PB_API	void*	UserDll_CreateUserExt(const tagUserInfo* user);		// 创建用户
	PB_API	int		UserDll_CloseUser(long serno, long userid, void* pInterface);		// 关闭与后台接口有关的用户信息
	PB_API	int		UserDll_CloseUserExt(tagRequestIn* in);		// 关闭与后台接口有关的用户信息
	PB_API	int		UserDll_CloseMidUser();	//关于柜台连接，由工作线程调用，目前CTP接口需要用到。
	PB_API	int		UserDll_ReleaseMemory(long serno, long userid, void* pInterface);		// 释放用户的临时内存


	//tagUserDllRequestOut.checkcode
	PB_API	int UserDll_TranslateRequest(const tagRequestIn* in, tagRequestOut* out);	// 处理请求
	PB_API	int UserDll_Heart(const tagRequestIn* in, tagRequestOut* out);

	//以下两个接口是在主程序与业务模块之间传递数据使用的，
	//pInfo:是对应用户的指针，可以为NULL，
	//type:enum QAT_CODE
	//	QAT_ERRMSG			= 1,			//错误信息
	//	QAT_DEPARTCODE		= 2,			//营业部代码
	//	QAT_CONNSTATE		= 3,			//连接状态，值为0或1,1表示连接
	//	QAT_ACCOUNT			= 4,			//帐号，用于记录日志和刷卡限制次数
	//	QAT_CONFIG			= 5,			//主要是配置的地址及信息等	_tagConfig
	//	QAT_DLLINFO			= 6,			//业务模块的信息	tagDLLVer
	//	QAT_NETADDR			= 7,			//本机网络地址
	//	QAT_USETIME			= 8,			//获取到期日期，为long型，如果不支持时返回QAT_RET_NOT,则主程序忽略
											//返回QAT_RET_FAIL时，需要查看返回的data，分别为-2,-1,0及正确的年月日
	//	QAT_USERINFO		= 9,			//连接用户信息，主程序使用本接口传递用户信息给业务模块，比如
											//m_nSerno,m_nClientSocket,传输的结构体是tagQATUserInfo


	//data,len:传递数据的指针和长度
	//return:
	//	QAT_RET_MEMSIZE_ERROR	= 1,		//给定的内存太小，新的大小在len中指定，但还是拷贝指定大小的数据
	//	QAT_RET_SUCCESS			= 0,		//成功
	//	QAT_RET_FAIL			= -1,		//失败
	//	QAT_RET_NOT				= -2		//不支持的代码

	//主程序向业务模块传递数据，目前只支持QAT_NETADDR
	PB_API	long	UserDll_Set(long serno, long userid, void* pInterface, long type, void* data, long len);

	//主程序获取业务模块数据，缓冲长度不够时，返回QAT_RET_MEMSIZE_ERROR，并设置len为需要的长度
	PB_API	long	UserDll_Get(long serno, long userid, void* pInterface, long type, void* data, long* len);


	//#define	LISTTYPE_USERINFO		1		//用户列表信息
	//#define	LISTTYPE_ADDRESSINFO	2		//后台地址列表信息
	//#define	LISTTYPE_ROUTEINFO		3		//转发服务器列表信息
	//获取某种类型的列表信息
	//type指明列表：LISTTYPE_USERINFO、LISTTYPE_ADDRESSINFO、LISTTYPE_ROUTEINFO
	//flag标志：DRAWALL、DRAWUPDATE，分别表示是初始化显示和更新显示
	//data,len：存储返回的数据缓冲
	//return:返回数据长度，为0或负数表示没有数据或出错
	//返回的数据格式:
	//开始为LIST_HEAD结构，剩下的为数据
	//数据包含字段信息和记录信息，它们之前用'\n'分隔开
	//字段信息块包含多个字段信息，各字段之前用'\t'分隔开；每个字段信息包含多个信息，用'|'分隔开，分别代表字段名、显示名、显示宽度、对齐方式
	//字段名目前不用，可以返回空；显示名是显示在列表头的名称、显示宽度为列表中字段宽度、对齐方式包括左('L')、中('M')、右('R')三种，默认为中
	//可能会包含多条记录，记录之前用'\n'分隔开；每条记录包含多个字段信息，字段之间用'\t'分隔开；每个字段有字段值和颜色两项，显示时按顺序显示
	//如果flag为更新时，则不需要字段信息块，即直接从记录开始，显示时不需要重新初始化整个列表，而只需要更新记录信息即可。
	PB_API	long	UserDll_GetList(long type, long flag, char* data, int len);

	//设置写日志、路径的函数指针
	PB_API void	UserDll_SetLogPathFunc(__SetLogPath	Func);
	PB_API void	UserDll_SetWriteLogFunc(__WriteLog Func);

	//实时调用业务模块的用户，用户可以做自己的事情，比如实时推数据给客户端
	//nDataLen存储返回的应答数据长度,
	//nErrorCode存储返回的错误号，同UserDll_TranslateRequest，错误号为-2时主程序会关闭用户
	//接口返回应答数据指针
	//没有应答数据时返回NULL
	PB_API	const char*	UserDll_Idle(long serno, long userid, void* pInterface, int& nDataLen, int& nErrorCode);

	PB_API	const char*	UserDll_Idle_Step(long serno, long userid, void* pInterface, int& nDataLen, int& nErrorCode,tagRequestOut* out);


	//设置函数指针
	PB_API void	UserDll_SetFunc(tagMainFuncPtr*	MainFunc, int size);

#endif
