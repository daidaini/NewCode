
//��ʼ��
int	UserDll_Init(const char* pszConfigFile)
{
	char tradeConfPath[] = "./mdll_trade.ini";
	if (LBargainBaseStepCom::InitCommonConfig(pszConfigFile, tradeConfPath) < 0)
		return -1;

	g_SysLogger.start();
	curl_global_init(CURL_GLOBAL_ALL);

	if (!CUserAuthEntification::GetInstance().Init())
	{
		WriteLog(LOG_SYSTEM, LOG_LEVEL_MAX, "�������ݿ�����ʧ��");
		::MessageBox(nullptr, "�������ݿ�����ʧ�ܣ�������ݿⲿ�����", "����", MB_OK);
		exit(-1);
	}
	CMockContracts::GetInstance().Start();

	if (atoi(g_ConfigTrade.m_PushData) != 0)
	{
		if (CHttpPushHandle::GetInstance().StartServer() != 0)
		{
			WriteLog(LOG_SYSTEM, LOG_LEVEL_MAX, "HTTP���ͷ�������ʧ��");
			::MessageBox(nullptr, "HTTP���ͷ�������ʧ�ܣ����˿��Ƿ�ռ��", "����", MB_OK);
			exit(-1);
		}
	}
	return 0;
}

// ��̬���ͷź���
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

// �����û�
void* UserDll_CreateUserExt(const tagUserInfo* info)
{
	LBargain* user = new LBargain;
	user->SetClientSocket(info);
	return user;
}
// �ر����̨�ӿ��йص��û���Ϣ
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

// �ر����̨�ӿ��йص��û���Ϣ
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

// ��������
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
	case QAT_DLLINFO:			//ҵ��ģ�����Ϣ
	{
		tagDLLVer dllver;
		strcpy(dllver.m_szSign, "PBDLL2.0");
		dllver.m_CommType = CT_STEPTYPE;//2��Э�� 1��Э��
		dllver.m_DllType[0] = 6;
		dllver.m_DllType[1] = 0;
		dllver.m_DllType[2] = -1;

		char str[512] = { 0 };
#ifdef	_DEBUG			
		strcpy(str, "���֤ȯģ�⽻������S2��(DEBUG)");
#else
		strcpy(str, "���֤ȯģ�⽻������S2��");
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
	case QAT_ACCOUNT:			//�ʺţ����ڼ�¼��־��ˢ�����ƴ���
	{
		if (!user)
			return QAT_RET_FAIL;

		user->GetAccount(data, len);
		break;
	}
	case QAT_CONNSTATE:			//����״̬��ֵΪ0��1,1��ʾ����
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

//9\n��־\nָ��\n��ʾ��\n��ʾ��\n��ʾ��\n��ʾ��\n��ʾ��\n��ʾ��\n��ʾ��
long GetPageNum(char* data, int len)
{
	STD::my_snprintf(data, len, "%d\n%s\n%s\n",
		2,
		"��־",
		"���׵�ַ"
		);
	return 2;
}

//��ȡĳ�����͵��б���Ϣ
//typeָ���б�LISTTYPE_USERINFO��LISTTYPE_ADDRESSINFO��LISTTYPE_ROUTEINFO
//flag��־��DRAWALL��DRAWUPDATE���ֱ��ʾ�ǳ�ʼ����ʾ�͸�����ʾ
//data,len���洢���ص����ݻ���
//return:�������ݳ��ȣ�Ϊ0������ʾû�����ݻ����
//���ص����ݸ�ʽ:
//��ʼΪLIST_HEAD�ṹ��ʣ�µ�Ϊ����
//���ݰ����ֶ���Ϣ�ͼ�¼��Ϣ������֮ǰ��'\n'�ָ���
//�ֶ���Ϣ���������ֶ���Ϣ�����ֶ�֮ǰ��'\t'�ָ�����ÿ���ֶ���Ϣ���������Ϣ����'|'�ָ������ֱ�����ֶ�������ʾ������ʾ��ȡ����뷽ʽ
//�ֶ���Ŀǰ���ã����Է��ؿգ���ʾ������ʾ���б�ͷ�����ơ���ʾ���Ϊ�б����ֶο�ȡ����뷽ʽ������('L')����('M')����('R')���֣�Ĭ��Ϊ��
//���ܻ����������¼����¼֮ǰ��'\n'�ָ�����ÿ����¼��������ֶ���Ϣ���ֶ�֮����'\t'�ָ�����ÿ���ֶ�Ŀǰֻ���ֶ�ֵһ���ʾʱ��˳����ʾ
//���flagΪ����ʱ������Ҫ�ֶ���Ϣ�飬��ֱ�ӴӼ�¼��ʼ����ʾʱ����Ҫ���³�ʼ�������б���ֻ��Ҫ���¼�¼��Ϣ���ɡ�
long UserDll_GetList(long type, long flag, char* data, int len)
{
	switch (type)
	{
	case LISTTYPE_ADDRESSINFO:	//��̨��ַ�б���Ϣ
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


//����д��־��·���ĺ���ָ��
void UserDll_SetLogPathFunc(__SetLogPath	Func)
{
	SetLogPath = Func;
}

void UserDll_SetWriteLogFunc(__WriteLog Func)
{
	WriteLog = Func;
}

//���ú���ָ��
void UserDll_SetFunc(tagMainFuncPtr*	MainFunc, int size)
{
	memset(&g_MainFuncPtr, 0, sizeof(g_MainFuncPtr));
	size = min(size, sizeof(g_MainFuncPtr));
	memcpy(&g_MainFuncPtr, MainFunc, size);
}

//ʵʱ����ҵ��ģ����û����û��������Լ������飬����ʵʱ�����ݸ��ͻ���
//nDataLen�洢���ص�Ӧ�����ݳ���,
//nErrorCode�洢���صĴ���ţ�ͬUserDll_TranslateRequest�������Ϊ-2ʱ�������ر��û�
//�ӿڷ���Ӧ������ָ��
//û��Ӧ������ʱ����NULL
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
