
//初始化
int	UserDll_Init(const char* pszConfigFile)
{
	char tradeConfPath[] = "./mdll_trade.ini";
	if (LBargainBaseStepCom::InitCommonConfig(pszConfigFile, tradeConfPath) < 0)
		return -1;

	g_SysLogger.start();
	curl_global_init(CURL_GLOBAL_ALL);

	if (!CUserAuthEntification::GetInstance().Init())
	{
		WriteLog(LOG_SYSTEM, LOG_LEVEL_MAX, "连接数据亏服务失败");
		::MessageBox(nullptr, "连接数据亏服务失败，检查数据库部署情况", "错误", MB_OK);
		exit(-1);
	}
	CMockContracts::GetInstance().Start();

	if (atoi(g_ConfigTrade.m_PushData) != 0)
	{
		if (CHttpPushHandle::GetInstance().StartServer() != 0)
		{
			WriteLog(LOG_SYSTEM, LOG_LEVEL_MAX, "HTTP推送服务启动失败");
			::MessageBox(nullptr, "HTTP推送服务启动失败，检查端口是否被占用", "错误", MB_OK);
			exit(-1);
		}
	}
	return 0;
}

// 动态库释放函数
int	UserDll_Release()
{
	CHttpPushHandle::GetInstance().StopServer();
	CUserAuthEntification::GetInstance().Release();
	CMockContracts::GetInstance().Stop();
	CMockContracts::GetInstance().Join();
	g_SysLogger.stop();

	curl_global_cleanup();
	g_Base.Release();
	return 0;
}

// 创建用户
void* UserDll_CreateUserExt(const tagUserInfo* info)
{
	LBargain* user = new LBargain;
	user->SetClientSocket(info);
	return user;
}
// 关闭与后台接口有关的用户信息
int	UserDll_CloseUser(long serno, long userid, void* pInterface)
{
	if (pInterface)
	{
		LBargain* user = (LBargain*)pInterface;
		user->DoLogout();
		delete user;
	}
	WriteLog(0, 100, "UserDll_CloseUser[%d]", userid);
	return 0;
}

// 关闭与后台接口有关的用户信息
int	UserDll_CloseUserExt(tagRequestIn* in)
{
	if (in->pInterface)
	{
		LBargain* user = (LBargain*)in->pInterface;
		user->DoLogout();
		delete user;
		in->pInterface = NULL;
		in->requestsize = 0;
	}
	else
	{
		in->requestsize = 0;
	}

	return in->requestsize;
}

int	UserDll_ReleaseMemory(long serno, long userid, void* pInterface)
{
	if (pInterface)
	{
		LBargain* user = (LBargain*)pInterface;
		user->Free();
	}

	return 0;
}

// 处理请求
int UserDll_TranslateRequest(const tagRequestIn* in, tagRequestOut* out)
{
	if (in->pInterface)
	{
		LBargain* user = (LBargain*)in->pInterface;
		user->SendAndRecv(in->request, in->requestsize, out);
		return out->checkcode;
	}
	else
	{
		out->checkcode = -1;
		out->out = NULL;
		out->outlen = 0;
		out->packagesize = 0;
	}
	return out->checkcode;
}

long UserDll_Set(long serno, long userid, void* pInterface, long type, void* data, long len)
{
	if (!data || len <= 0)
		return QAT_RET_FAIL;

	return QAT_RET_NOT;
}

long UserDll_Get(long serno, long userid, void* pInterface, long type, void* data, long* len)
{
	LBargain* user = (LBargain*)pInterface;

	if (!data || *len <= 0)
		return QAT_RET_FAIL;

	memset(data, 0, *len);

	switch (type)
	{
	case QAT_DLLINFO:			//业务模块的信息
	{
		tagDLLVer dllver;
		strcpy(dllver.m_szSign, "PBDLL2.0");
		dllver.m_CommType = CT_STEPTYPE;//2新协议 1老协议
		dllver.m_DllType[0] = 6;
		dllver.m_DllType[1] = 0;
		dllver.m_DllType[2] = -1;

		char str[512] = { 0 };
#ifdef	_DEBUG			
		strcpy(str, "汇点证券模拟交易网关S2版(DEBUG)");
#else
		strcpy(str, "汇点证券模拟交易网关S2版");
#endif

		dllver.m_lUpdateDate = UpdateDate;
		dllver.m_Ver.w.ver = MainVer * 10 + SubVer;
		dllver.m_Ver.w.build = BuildVer;

		STD::my_snprintf(dllver.m_szDescription, sizeof(dllver.m_szDescription) - 1, "V%d.%d.%d.%d(%ld)(%s)",
			MainVer, SubVer, PubVer, BuildVer, dllver.m_lUpdateDate, str);

		LBargainBaseStepCom::m_GatewayVersion = dllver.m_szDescription;
		if (*len < sizeof(dllver))
		{
			memcpy(data, &dllver, *len);
			*len = sizeof(dllver);
			return QAT_RET_MEMSIZE_ERROR;
		}
		char s_ver_shields[64];
		CIniFile tmpini("./shields.ini");
		STD::my_snprintf(s_ver_shields, sizeof(s_ver_shields), "V%d.%d.%d.%d(%ld)", MainVer, SubVer, PubVer, BuildVer, dllver.m_lUpdateDate);
		tmpini.WriteString("status", "server_dll_ver", s_ver_shields);
		tmpini.WriteString("status", "server_ver", s_ver_shields);

		memcpy(data, &dllver, sizeof(dllver));
		return QAT_RET_SUCCESS;
	}
	case QAT_ACCOUNT:			//帐号，用于记录日志和刷卡限制次数
	{
		if (!user)
			return QAT_RET_FAIL;

		user->GetAccount(data, len);
		break;
	}
	case QAT_CONNSTATE:			//连接状态，值为0或1,1表示连接
	{
		if (!user)
			return QAT_RET_FAIL;

		BYTE state = user->GetConnectStat();

		if (state > 0)
			state = 1;

		memcpy(data, &state, sizeof(BYTE));
		break;
	}
	default:
		return QAT_RET_NOT;
	};

	return QAT_RET_SUCCESS;
}

//9\n日志\n指数\n显示三\n显示四\n显示五\n显示六\n显示七\n显示八\n显示九
long GetPageNum(char* data, int len)
{
	STD::my_snprintf(data, len, "%d\n%s\n%s\n",
		2,
		"日志",
		"交易地址"
		);
	return 2;
}

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
//可能会包含多条记录，记录之前用'\n'分隔开；每条记录包含多个字段信息，字段之间用'\t'分隔开；每个字段目前只有字段值一项，显示时按顺序显示
//如果flag为更新时，则不需要字段信息块，即直接从记录开始，显示时不需要重新初始化整个列表，而只需要更新记录信息即可。
long UserDll_GetList(long type, long flag, char* data, int len)
{
	switch (type)
	{
	case LISTTYPE_ADDRESSINFO:	//后台地址列表信息
	case LISTTYPE_PAGE_2:
		return g_Base.GetAddressInfo(flag, data, len);

	case LISTTYPE_GET_NUM:
		return GetPageNum(data, len);
	case LISTTYPE_GET_ACCOUNT_NUM:
		return g_Base.GetAccountData(flag, data, len);
	default:
		return NULL;
	}
}


//设置写日志、路径的函数指针
void UserDll_SetLogPathFunc(__SetLogPath	Func)
{
	SetLogPath = Func;
}

void UserDll_SetWriteLogFunc(__WriteLog Func)
{
	WriteLog = Func;
}

//设置函数指针
void UserDll_SetFunc(tagMainFuncPtr*	MainFunc, int size)
{
	memset(&g_MainFuncPtr, 0, sizeof(g_MainFuncPtr));
	size = min(size, sizeof(g_MainFuncPtr));
	memcpy(&g_MainFuncPtr, MainFunc, size);
}

//实时调用业务模块的用户，用户可以做自己的事情，比如实时推数据给客户端
//nDataLen存储返回的应答数据长度,
//nErrorCode存储返回的错误号，同UserDll_TranslateRequest，错误号为-2时主程序会关闭用户
//接口返回应答数据指针
//没有应答数据时返回NULL
const char*	UserDll_Idle_Step(long serno, long userid, void* pInterface, int& nDataLen, int& nErrorCode, tagRequestOut* out)
{
	if (pInterface)
	{
		LBargain* user = (LBargain*)pInterface;

		nErrorCode = user->Idle(out);
		nDataLen = out->outlen;
		out->checkcode = nErrorCode;
		if (nDataLen > 0)
		{
			return out->out;
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		nDataLen = 0;
		nErrorCode = OR_NET_ERROR;
		return NULL;
	}
}
