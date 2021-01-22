#ifndef	__PB_API_H__
#define __PB_API_H__

#define	MAX_USER_NUM		65536	// ֧������û�

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
		char*	request;		//��������
		int		requestsize;	//�����С
	} tagRequestIn;

	typedef struct {
		int		checkcode;		//������Ϣ��0��ʾ������������>0��ʾ�Ѵ��������󣬸�����ʾ���󣬿ɹر��û�
		int		packagesize;	//�Ѵ��������С

		char*	out;			//����Ӧ������ָ��
		int		outlen;			//����Ӧ�����ݴ�С
		//int		errorcode;
	} tagRequestOut;

#pragma pack(1)
	typedef struct {
		char		username[32];
		char		pwd[16];
		INT32		fwbm;					//����������	22	INT32
		char		fwmc[32];				//����������	23	WCHAR(32)
		INT32		currusernum;			//��ǰ�û���	24	INT32
		__int32		maxusernum;				//����û���	25	INT32
		char		maxusertime[32];		//����û�������ʱ��	26	CHAR(19) Yyyy-mm-dd hh:mm:ss
		char		servicetime[32];		//������ʱ��	27	CHAR(19)
		INT32		status;					//����״̬	28	INT80:�쳣��1������ 30�ֶο�ָ���쳣ԭ��
		char		statusname[8];			//״̬����	29	WCHAR(10)
		char		remark[512];			//��ע	30	WCHAR(1024)
		char		worktime[32];			//������Ĺ���ʱ��	31	CHAR(20) D-hh:mm:ss����ʾ�����˶����켰ʱ����
		char		cpurate[16];			//CPUʹ����	32	CHAR(10)
		char		memoryrate[16];			//�ڴ�ʹ����	33	CHAR(10)
		int			SendBytesPerSecond;		//ÿ������
		int			maxSendBytesPerSecond;	//���ÿ������
		char		Version[128];			//ҵ��ģ��汾
		int			MaxUsrNum;				//���õ���������û���
		char		DumpTime[64];			//����ʱ��
		int			CPUCount;				//CPU����
		int			TotalPhyMemory;			//�����ڴ��С����λ��G��
		double		CPUFreq;				//��Ƶ ��λG
	}tagServiceInfo;
#pragma pack()
	
	typedef bool	(* __GetServiceInfo)(tagServiceInfo* info, int size);
	typedef void*	(* __MemoryManage_Alloc)(int& NeedSizeAndRealSize);
	typedef bool	(* __MemoryManage_Push)(void* mem);

	typedef struct {
		__GetServiceInfo			pgetServiceInfo;	//��ȡ��������Ϣ
	} tagMainFuncPtr;

	#define PB_API extern "C"  __declspec(dllexport)

	// ��̬���ʼ��������
	// pszConfigFile:�����ļ���
	// ���ش���ţ�0�ɹ�������ʧ��
	PB_API	int		UserDll_Init(const char* pszConfigFile);
	PB_API	int		UserDll_Init_Path(const char* pszConfigFile,const char*);
	PB_API	int		UserDll_Release();			// ��̬���ͷź���

	// �����������󷵻�0ʱ��ʾ�ɹ���������ʾʧ��
	PB_API	void*	UserDll_CreateUser(long serno, long userid);		// �����û�
	PB_API	void*	UserDll_CreateUserExt(const tagUserInfo* user);		// �����û�
	PB_API	int		UserDll_CloseUser(long serno, long userid, void* pInterface);		// �ر����̨�ӿ��йص��û���Ϣ
	PB_API	int		UserDll_CloseUserExt(tagRequestIn* in);		// �ر����̨�ӿ��йص��û���Ϣ
	PB_API	int		UserDll_CloseMidUser();	//���ڹ�̨���ӣ��ɹ����̵߳��ã�ĿǰCTP�ӿ���Ҫ�õ���
	PB_API	int		UserDll_ReleaseMemory(long serno, long userid, void* pInterface);		// �ͷ��û�����ʱ�ڴ�


	//tagUserDllRequestOut.checkcode
	PB_API	int UserDll_TranslateRequest(const tagRequestIn* in, tagRequestOut* out);	// ��������
	PB_API	int UserDll_Heart(const tagRequestIn* in, tagRequestOut* out);

	//���������ӿ�������������ҵ��ģ��֮�䴫������ʹ�õģ�
	//pInfo:�Ƕ�Ӧ�û���ָ�룬����ΪNULL��
	//type:enum QAT_CODE
	//	QAT_ERRMSG			= 1,			//������Ϣ
	//	QAT_DEPARTCODE		= 2,			//Ӫҵ������
	//	QAT_CONNSTATE		= 3,			//����״̬��ֵΪ0��1,1��ʾ����
	//	QAT_ACCOUNT			= 4,			//�ʺţ����ڼ�¼��־��ˢ�����ƴ���
	//	QAT_CONFIG			= 5,			//��Ҫ�����õĵ�ַ����Ϣ��	_tagConfig
	//	QAT_DLLINFO			= 6,			//ҵ��ģ�����Ϣ	tagDLLVer
	//	QAT_NETADDR			= 7,			//���������ַ
	//	QAT_USETIME			= 8,			//��ȡ�������ڣ�Ϊlong�ͣ������֧��ʱ����QAT_RET_NOT,�����������
											//����QAT_RET_FAILʱ����Ҫ�鿴���ص�data���ֱ�Ϊ-2,-1,0����ȷ��������
	//	QAT_USERINFO		= 9,			//�����û���Ϣ��������ʹ�ñ��ӿڴ����û���Ϣ��ҵ��ģ�飬����
											//m_nSerno,m_nClientSocket,����Ľṹ����tagQATUserInfo


	//data,len:�������ݵ�ָ��ͳ���
	//return:
	//	QAT_RET_MEMSIZE_ERROR	= 1,		//�������ڴ�̫С���µĴ�С��len��ָ���������ǿ���ָ����С������
	//	QAT_RET_SUCCESS			= 0,		//�ɹ�
	//	QAT_RET_FAIL			= -1,		//ʧ��
	//	QAT_RET_NOT				= -2		//��֧�ֵĴ���

	//��������ҵ��ģ�鴫�����ݣ�Ŀǰֻ֧��QAT_NETADDR
	PB_API	long	UserDll_Set(long serno, long userid, void* pInterface, long type, void* data, long len);

	//�������ȡҵ��ģ�����ݣ����峤�Ȳ���ʱ������QAT_RET_MEMSIZE_ERROR��������lenΪ��Ҫ�ĳ���
	PB_API	long	UserDll_Get(long serno, long userid, void* pInterface, long type, void* data, long* len);


	//#define	LISTTYPE_USERINFO		1		//�û��б���Ϣ
	//#define	LISTTYPE_ADDRESSINFO	2		//��̨��ַ�б���Ϣ
	//#define	LISTTYPE_ROUTEINFO		3		//ת���������б���Ϣ
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
	//���ܻ����������¼����¼֮ǰ��'\n'�ָ�����ÿ����¼��������ֶ���Ϣ���ֶ�֮����'\t'�ָ�����ÿ���ֶ����ֶ�ֵ����ɫ�����ʾʱ��˳����ʾ
	//���flagΪ����ʱ������Ҫ�ֶ���Ϣ�飬��ֱ�ӴӼ�¼��ʼ����ʾʱ����Ҫ���³�ʼ�������б���ֻ��Ҫ���¼�¼��Ϣ���ɡ�
	PB_API	long	UserDll_GetList(long type, long flag, char* data, int len);

	//����д��־��·���ĺ���ָ��
	PB_API void	UserDll_SetLogPathFunc(__SetLogPath	Func);
	PB_API void	UserDll_SetWriteLogFunc(__WriteLog Func);

	//ʵʱ����ҵ��ģ����û����û��������Լ������飬����ʵʱ�����ݸ��ͻ���
	//nDataLen�洢���ص�Ӧ�����ݳ���,
	//nErrorCode�洢���صĴ���ţ�ͬUserDll_TranslateRequest�������Ϊ-2ʱ�������ر��û�
	//�ӿڷ���Ӧ������ָ��
	//û��Ӧ������ʱ����NULL
	PB_API	const char*	UserDll_Idle(long serno, long userid, void* pInterface, int& nDataLen, int& nErrorCode);

	PB_API	const char*	UserDll_Idle_Step(long serno, long userid, void* pInterface, int& nDataLen, int& nErrorCode,tagRequestOut* out);


	//���ú���ָ��
	PB_API void	UserDll_SetFunc(tagMainFuncPtr*	MainFunc, int size);

#endif
