
#pragma once

#include <Windows.h>
#include <atomic>


enum PTK_TASKTYPE
{
	TASK_NULL = 0,

	TASK_LOGIN = 1,		// ��¼
	TASK_PROCEEDLOGIN = 2,		// ������¼
	TASK_LOGOUT = 3,		// ע��

	TASK_QUERY_NOTICE = 4,		// �龭����֪ͨ
	TASK_QUERY_SETTLE = 5,		// ����㵥
	TASK_CONFIRM_SETTLE = 6,		// ȷ�Ͻ��㵥
	TASK_QUERY_CONTRACT = 7,		// ���Լ
	TASK_QUERY_TRADENUMBER = 8,		// �齻�ױ���
	TASK_BATCH_QUERY = 9,		// ������ѯ
	TASK_QUERY_ORDER = 10,		// �鵱��ί��
	TASK_QUERY_TRADE = 11,		// ��ɽ�
	TASK_QUERY_TRADE_BYDATE = 12,		// ����ʷ�ɽ�
	TASK_QUERY_POSITION = 13,		// ��ֲ�

	//	TASK_QUERY_POSITIONDETAIL	= 14,	// ��ֲ�
	TASK_QUERY_ACCOUNT = 15,		// ���˻��ʽ�
	TASK_QUERY_TRADEPARAM = 16,		// �齻�ײ���
	TASK_QUERY_MARGINRATE = 17,		// �鱣֤����
	TASK_QUERY_COMMISSIONRATE = 18,	// ����������
	TASK_QUERY_BANK = 19,		// ������
	TASK_QUERY_BANKACCOUNT = 20,		// �������˺�
	TASK_QUERY_CFMMC = 21,		// �鱣֤��������

	TASK_QUERY_MAX = 22,		// ���������
	TASK_INSERT_ORDER = 23,		// �µ�
	TASK_INSERT_ORDER_DIRECT = 24,	// �µ����ڲ����ܣ�
	TASK_CANCEL_ORDER = 25,		// ����
	TASK_NEXT_SCRIPT = 26,		// ִ����һ���ű�
	TASK_CHANGE_PASSWORD = 27,		// �޸Ľ�������
	TASK_QUERY_BANKBALANCE = 28,		// ���������
	TASK_QUERY_BANKTRANSFER = 29,		// ��ת�˼�¼
	TASK_BANKTRANSFER = 30,		// ת��
	TASK_CHANGE_BANKPASSWORD = 31,	//�޸���������
	TASK_QUERY_BANKTRANSFERWITHLSH = 32,		// ��ָ����ˮ��ת�˼�¼
	TASK_NEW_LOGIN_6011 = 33,		//������Э��������ĵ�¼����һ���ǽ�����Կ��
	TASK_NEW_LOGIN_3 = 34,				//	������Э��������ĵ�¼,�ڶ����ǽ���������Կ���������ǵ�¼

	//TASK_RELOGIN			= 40,		//�ص�¼
	TASK_PROCEEDRELOGIN = 41,		//�����ص�¼
	TASK_TESTCONNECTING = 42,		//���١��������ӡ�����

	TASK_BQUERY_DIRECT = 50,		//�µ�������������ˢ������
	TASK_BQUERY_VOLUNT = 51,		//ˢ�°�ť��Ӧ����

	TASK_QUERY_PawnStock = 1000,		//��ѯ����֤ȯ
	TASK_QUERY_SubjectStock = 1001,		//��ѯ���֤ȯ
	TASK_QUERY_FinanceCredit = 1002,		//���������ò�ѯ

	TASK_QUERY_TicketCredit = 1003,		//����ȯ���ò�ѯ

	TASK_QUERY_FinanceAndTicketAmount = 1004,		//��ѯ���ø�ծ����(�������ʺ���ȯ��ծ)

	TASK_QUERY_FinanceList = 1005,		//������ϸ��ѯ

	TASK_QUERY_TicketList = 1006,		//��ȯ��ϸ��ѯ

	TASK_QUERY_DebtList = 1007,		//��ծ��ˮ��ѯ

	TASK_QUERY_CreditStock = 1008,		//���ÿͻ���ת�뵣��֤ȯ��ѯ

	TASK_QUERY_AssetLiability = 1009,		//�ʲ���ծ��ѯ

	TASK_QUERY_PawnTransition = 1010,		//�����ﻮת

	TASK_QUERY_DisPawnTransition = 1011,		//�����ﻮת����

	TASK_QUERY_MARGIN_DisEntrust = 1012,		//������ȯί�г���

	TASK_QUERY_MarginRetMoney = 1013,		//ֱ�ӻ���

	TASK_QUERY_MarginRetStock = 1014,		//ֱ�ӻ�ȯ

	TASK_REQUEST_COMMON = 2000		//ͨ�ýӿ�
};


enum PTK_ERRCODE
{
	PTKE_RISK = -100,		//���ղ�ƥ��
	PTKE_SUCCESS = 0,		// �ɹ�
	PTKE_ERROR,				// ����
	PTKE_OVERFLOW,			// ���
	PTKE_PARAM,				// ��������
	PTKE_RESOURCE,			// ��Դ����
	PTKE_MEMORY,			// �ڴ治��
	PTKE_DLL_MISSING,		// dll�ļ���ʧ
	PTKE_API_INIT,			// API�ӿڳ�ʼ��ʧ��
	PTKE_LOGIN,				// ��¼ʧ��
	PTKE_GATE_RESTORE,		// ��������
	PTKE_PASSWORD,			// �������
	PTKE_NOTSUPPORTED,		// ��֧��
	PTKE_NOTREADY,			// δ����
	PTKE_NOTEXIST,			// Ŀ�겻����
	PTKE_NETWORK,			// �������
	PTKE_ABORT,				// ��������ֹ
	PTKE_TIMEOUT,			// ��ʱ

	PTKE_VOLUMELIMIT = 30,	// ������������
	PTKE_CONTRACT,			// ��Լ������
	PTKE_REFPRICE,			// �ο��ۣ����ּۡ��ҵ��ۡ���ͣ�ۡ���ͣ�۵ȣ�Ϊ0
	PTKE_PRICE,				// �۸���ȷ
	PTKE_PRICELIMIT,		// �۸񳬹�����
	PTKE_OPENLIMIT,			// ���ֳ�������
	PTKE_LOSSLIMIT,			// ���𳬹�����
	PTKE_MARGINLIMIT,		// ��֤�𳬹�����

	PTKE_MARKETCLOSED = 50,	// δ���ڿ���״̬
	PTKE_ALLTRADED,			// ί����ȫ���ɽ�
};


enum PTK_PLATFORM		// ����ƽ̨
{
	PPF_SFIT_F = 0,		// ���ڼ����ڻ�
	PPF_JSD_F = 1,		// ���˴��ڻ�
	PPF_HS_F = 2,		// �����ڻ�
	PPF_DD_F = 3,		// �����ڻ�
	PPF_JSD2_F = 4,		// ���˴��ڻ� V2
	PPF_HS2_F = 5,		// �����ڻ� V2
	//	PPF_JSDB2B_F	= 6,		//���˴�B2B�ӿ�
	PPF_SFIT_KS_F = 7,		//	���˴��CTP
	PPF_STANDARD_Future = 8,			//��׼�ڻ�,���ӱ�׼����

	PPF_LAST_F = 29,			// 

	PPF_START_S = 30,
	PPF_SFIT_S = 30,		// ���ڼ�����Ʊ
	PPF_SFIT_Q = 31,		// ���ڼ�����Ʊ��Ȩ
	PPF_SFIT_S2 = 32,		// ���ڼ�����Ʊ CTP2��̨
	PPF_SFIT_Q2 = 33,		// ���ڼ�����Ʊ��Ȩ CTP2��̨
	PPF_FCh_S = 34,		// �ɴ���Ʊ�ֻ�
	PPF_FCh_Q = 35,		// �ɴ���Ʊ��Ȩ
	PPF_STANDARD_S = 36,		//��׼�ֻ���
	PPF_STANDARD_Q = 37,		//��׼��Ȩ��
	PPF_STANDARD_RZRQ = 38,	//��׼������ȯ��
	PPF_STANDARD_S_NEW = 39,	//��Ʊ������Э���
	PPF_STANDARD_Q_NEW = 40,		//��׼��Ȩ�������Э���
	PPF_STANDARD_RZRQ_NEW = 41,	//��׼������ȯ�������Э���
	PPF_STANDARD_GOLD_NEW = 42,	//��׼�ƽ���Э���
	PPF_STANDARD_GOLD = 43,		//��׼�ƽ�

	PPF_OES_S = 50,		//����ͨ���ٽ���ϵͳ�ֻ���
	PPF_LAST_S = 59,			// 

	PPF_PFHJ_F = 60,	// �ַ��ƽ�
	PPF_JSDHJ_F = 61,	//���˴�ƽ�

	//100 -- 200 ��Э�� 
	PPF_STADARD_TRADE = 100,		//��Э�齻��
	//201 -- 300 �ڻ���
	PPF_SFIT_FUTURE = 201,			//���ڼ����ڻ�
	PPF_KS_FUTURE = 202,		//���˴�B2C�ڻ�
	PPF_HSFUFX_FUTURE = 203,	//����UFX�ڻ�����

};

#define MAX_ACCOUNT_ID_LEN 32

struct CAccountInfo
{
	PTK_PLATFORM Platform;
	char AccountID[MAX_ACCOUNT_ID_LEN];

	bool operator==(const CAccountInfo& r)
	{
		return (Platform == r.Platform && strcmp(AccountID, r.AccountID) == 0);
	}
};

// ��������
struct Task
{
	Task()
	{
		memset(this, 0, sizeof(*this));
		RequestNo = GenerateRequestNo();
	}
	// �ύ������˺�
	CAccountInfo Account;
	// ��������
	PTK_TASKTYPE uType;
	// ִ�н��
	PTK_ERRCODE	 uResult;
	// �������
	int iReqSn;
	// ������ڲ����ܺ�
	int	funcno;
	// ��������ʱ�����
	int	RequestNo;

	bool operator<(const Task& rhs) const
	{
		return funcno < rhs.funcno || (funcno == rhs.funcno && uType < rhs.uType);
	}

	static int GenerateRequestNo()
	{
		static std::atomic_int requestno;
		return ++requestno;
	}
};