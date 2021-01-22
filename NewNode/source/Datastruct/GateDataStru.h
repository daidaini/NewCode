#ifndef DataLH
#define DataLH
//#include <Afxtempl.h>
//baimh,20060731���������ʱ����mfc������Afxtempl.h����뱨��
//TCHAR.h��_T
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

#define	LISTTYPE_USERINFO		1		//�û��б���Ϣ
#define	LISTTYPE_ADDRESSINFO	2		//��̨��ַ�б���Ϣ
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
#define LISTTYPE_GET_ACCOUNT_NUM 110  //��ѯ���ص�¼�ϸ���ƽ̨���û�����

#define	DRAWALL					0		//��ʾ����
#define	DRAWUPDATE				1		//���¼�¼��Ϣ

#define	MAX_ROUTE_ADDRESS_NUM	64		//����̨·����Ϣ
#define	MAX_SAME_ADDRESS_NUM	5		//��ͬ·��ʱ������ַ��

enum InfoType
{
	CI_UPDATECOUNT,
	CI_ADDINFO,
	CI_UPDATEINFO,
	CI_DELINFO,
	CI_CONN,			//���ӳɹ�
	CI_NOTCONN,			//����ʧ��
};

enum OPERATION_RESULT // ������ɽ��
{
	//OR_CURRENT_LIMMIT_ERROR = -10,	//�����������CTP����ʾÿ����������δ�����������
	OR_ACCORPWD_ERROR	= -9,	//�˺Ż����������
	
	OR_UNLOGIN_ERROR	= -8,	//δ��¼ ������6����
	OR_LOGIN_EXIT     = -7,		//�ظ���¼���˻�����
	OR_FUNCTIME_ERROR = -6,		//	�������ƣ���ֹƵ������ͬһ������
	OR_TYPE_ERROR   = -5,		//	��֧�ֵĵ�¼������
	OR_NOFUNC_ERROR = -4,		//	û��ʵ�ֵĹ���
	OR_CONNECT_FAIL = -3,		//	���̨����ʧ��
	OR_NET_ERROR = -2,			//	�������ӶϿ�����ʧ�ܣ���������������������ò���ֹ�����Ͽ��ͻ��˺͹�̩������
	OR_ERRMSG_ERROR = -1,		//	�����ɹ������ؽ�������С���㣬�д�����ͷ��ء����߿ͻ����ǷǷ��û�
	OR_NOREC_ERROR = 0,			//	û�н�����ء���������Ϊ��̨�޴˹��ܡ�(���ڽ�֤���������󷵻أ�4��ȡ����������0)
	OR_SUCCESS = 1,
	OR_ELIGCHECK_ERROR	= -99,		//�ͻ��ʵ��Բ�����  �ϴ���ţ�����
	OR_NO_TRADING_TIME	 = -98,		//���ڽ���ʱ��
									//��CTP���ݻر��������ش���
									//���������������ڽ���ʱ��ĺ����������˴����ֱ�ӱ����ơ����ڽ���ʱ�䡱������Ϣ

	OR_RISKMISSMATCH_ERROR = -100,	//�ͻ��ʵ��Բ�ƥ��  ����Ҫǩ��Խ��Э�飩
	OR_PASSWORDKEY_EXPIRE = -101	//���봮����ʧЧ
};


enum QAT_CODE{							//������Ҫ���û��ȡ�����
	//QAT_ERRCODE			= 0,			//�������
	QAT_ERRMSG			= 1,			//������Ϣ
	QAT_DEPARTCODE		= 2,			//Ӫҵ������
	QAT_CONNSTATE		= 3,			//����״̬��ֵΪ0��1,1��ʾ����
	QAT_ACCOUNT			= 4,			//�ʺ�|ƽ̨��Ϣ|�ͻ��˰汾��|
										
	QAT_CONFIG			= 5,			//��Ҫ�����õĵ�ַ����Ϣ��	SiteInfo
	QAT_DLLINFO			= 6,			//ҵ��ģ�����Ϣ	tagDLLVer
	QAT_NETADDR			= 7,			//���������ַ
	QAT_USETIME			= 8,			//��ȡ�������ڣ�Ϊlong�ͣ������֧��ʱ����QAT_RET_NOT,�����������
										//����QAT_RET_FAILʱ����Ҫ�鿴���ص�data���ֱ�Ϊ-2,-1,0����ȷ��������
	QAT_USERINFO		= 9,			//�����û���Ϣ��������ʹ�ñ��ӿڴ����û���Ϣ��ҵ��ģ�飬����
										//m_nSerno,m_nClientSocket,����Ľṹ����tagQATUserInfo
	QAT_HQDLLINFO		= 10,			//����ģ����Ϣ		tagDLLVer

	//QAT_MAIN_FUNC_PTR	= 11,			//���ڽ��������һЩ��׼����ָ�봫�ݸ���һ��(tagMainFuncPtr)
};

enum QAT_RET_CODE {						//���������������ķ���ֵ
	QAT_RET_MEMSIZE_ERROR	= 1,		//�������ڴ�̫С���µĴ�С��len��ָ���������ǿ�����ָ����С������
	QAT_RET_SUCCESS			= 0,		//�ɹ�
	QAT_RET_FAIL			= -1,		//ʧ��
	QAT_RET_NOT				= -2		//��֧�ֵĴ���
};

//����Э�����һ��Э��ռ��һ��λ
enum COMM_TYPE
{
	CT_UNKOWN			= 0,
	CT_OLDTYPE			= 1,	//��Э��
	CT_STEPTYPE			= 2,		//��Э��
	CT_STEPTYPE_AES		= 3     //STEPЭ�� ʹ��AES����
};

#pragma pack(1)
struct ConInfo
{
	time_t MaxUserTime;			//��̨�����������ʱ��
	long MaxUser;				//����û���
	long CurUser;				//����û���
};
struct OneSite
{
	UINT port;				//��̨�˿ں�
	char IP[20];				//��̨IP��ַ
	BYTE szStat;				//״̬�� 0x00δ���  0x01������ 0x02 �Ͽ�	0x03 ������
	ConInfo UserInfo;			//�û�������Ϣ
	char szRemark[30];		//��������
	BYTE bConnectFlag;		//���̨��״̬����ʾ�����ɹ��ʺ��״̬��0Ϊ��֧�֣�1Ϊ������2Ϊ�쳣,20070202�������,baimh
	char LogPara[256];		//���Ӳ���
};

//վ������
struct SiteInfo
{
	long nAddressCount;		//��ַ����
	OneSite Address[32];		//��ַ��Ϣ
};

struct tagDLLVer
{
	char m_szSign[10];		// dll��ʶ���̶�ΪQLDLL�����ִ�Сд
	char m_szIdentify[20];	// �汾��ʶ����ʶ��̨���̰汾��"KD25,KD32"
	long m_lUpdateDate;		// �������ڣ�dll��������
	union DLL_VERSION	
	{
		long l;
		struct {
			unsigned short ver;		// ��3.1-->31
			unsigned short build;	// �ڲ���3λ:001
		}w;
	}m_Ver;				// dll�汾

	char m_szDescription[512];
	int	m_DllType[10];		//���Ͷ�����������һ������ֵΪ-1��ʾû����
								//DLL�����ͬί��Э���ﶨ��ġ���¼���
								//0:��ͨ�����
								//5:������ȯ����
								//6:������Ȩ����
	COMM_TYPE m_CommType;		//��ֵ��ʾҵ��ģ��֧�ֵ�Э�����࣬ͨѶģ��ʹ�ñ�ֵ���ж�ҵ��ģ��֧�ֵ�Э�����
	char m_DllType_Com[10];  //Com���ý���ģ��֧�ֵ�����    Comû������ Ĭ�Ͻ���ģ���Լ������
} ;					//����ҵ��̬����Ϣ

struct tagQATUserInfo
{
	int	m_nSerno;			// �û��������
	int	m_nUserID;			// �û�ΨһID��
	SOCKET m_nClientSocket;	// �洢�ͻ���socket
};	//����QAT_USERINFO��Ϣʱ�Ľṹ��

struct LIST_HEAD
{
	long size;
	long type;
	long flag;
	long recordnum;
	long fieldnum;
	char title[80];
};

//�û���¼��Ϣͳ��
struct UserLogStat
{
	long MaxUser_MI; //IOS�ֻ��û����������
	long CurUser_MI; //IOS�ֻ��û���ǰ������
	long MaxUser_MA; //��׿�ֻ��û����������
	long CurUser_MA; //��׿�ֻ��û���ǰ������ 
	long MaxUser_PC; //PC�û����������
	long CurUser_PC; //PC����ǰ������
};

struct VerHead
{
	char head[16];		//pengbo
	int	version;		//0--�����ܣ�1--����
	int	fileLen;		//�ļ����ݳ���
};

struct MTC_FieldInfo
{
 	int fieldno;
	char fieldname[64];
};

struct tagKeyFileHead
{
	unsigned short checkcode;	//�������ֽ��������������
	char sign[8];			//PTTA0002
};

//�ڶ���
struct tagKeyData	//��96�ֽ�
{	
	unsigned short checkcode;
	INT32 ver;					//0
	INT32 updatetime;
	char AuthCode[65];			//��֤��
	char unused[21];				//δ�ò���
};

#pragma pack()

#endif
