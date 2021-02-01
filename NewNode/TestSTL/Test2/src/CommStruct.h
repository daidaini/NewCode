
#pragma once

#include <Windows.h>
#include <atomic>


enum PTK_TASKTYPE
{
	TASK_NULL = 0,

	TASK_LOGIN = 1,		// 登录
	TASK_PROCEEDLOGIN = 2,		// 继续登录
	TASK_LOGOUT = 3,		// 注销

	TASK_QUERY_NOTICE = 4,		// 查经纪商通知
	TASK_QUERY_SETTLE = 5,		// 查结算单
	TASK_CONFIRM_SETTLE = 6,		// 确认结算单
	TASK_QUERY_CONTRACT = 7,		// 查合约
	TASK_QUERY_TRADENUMBER = 8,		// 查交易编码
	TASK_BATCH_QUERY = 9,		// 批量查询
	TASK_QUERY_ORDER = 10,		// 查当日委托
	TASK_QUERY_TRADE = 11,		// 查成交
	TASK_QUERY_TRADE_BYDATE = 12,		// 查历史成交
	TASK_QUERY_POSITION = 13,		// 查持仓

	//	TASK_QUERY_POSITIONDETAIL	= 14,	// 查持仓
	TASK_QUERY_ACCOUNT = 15,		// 查账户资金
	TASK_QUERY_TRADEPARAM = 16,		// 查交易参数
	TASK_QUERY_MARGINRATE = 17,		// 查保证金率
	TASK_QUERY_COMMISSIONRATE = 18,	// 查手续费率
	TASK_QUERY_BANK = 19,		// 查银行
	TASK_QUERY_BANKACCOUNT = 20,		// 查银行账号
	TASK_QUERY_CFMMC = 21,		// 查保证金监控中心

	TASK_QUERY_MAX = 22,		// 查最大数量
	TASK_INSERT_ORDER = 23,		// 下单
	TASK_INSERT_ORDER_DIRECT = 24,	// 下单（内部功能）
	TASK_CANCEL_ORDER = 25,		// 撤单
	TASK_NEXT_SCRIPT = 26,		// 执行下一个脚本
	TASK_CHANGE_PASSWORD = 27,		// 修改交易密码
	TASK_QUERY_BANKBALANCE = 28,		// 查银行余额
	TASK_QUERY_BANKTRANSFER = 29,		// 查转账记录
	TASK_BANKTRANSFER = 30,		// 转账
	TASK_CHANGE_BANKPASSWORD = 31,	//修改银行密码
	TASK_QUERY_BANKTRANSFERWITHLSH = 32,		// 查指定流水的转账记录
	TASK_NEW_LOGIN_6011 = 33,		//用于新协议流程里的登录，第一次是交换密钥，
	TASK_NEW_LOGIN_3 = 34,				//	用于新协议流程里的登录,第二次是交换密码密钥，第三次是登录

	//TASK_RELOGIN			= 40,		//重登录
	TASK_PROCEEDRELOGIN = 41,		//继续重登录
	TASK_TESTCONNECTING = 42,		//测速、测试连接、心跳

	TASK_BQUERY_DIRECT = 50,		//下单，撤单后立即刷新请求
	TASK_BQUERY_VOLUNT = 51,		//刷新按钮响应请求

	TASK_QUERY_PawnStock = 1000,		//查询担保证券
	TASK_QUERY_SubjectStock = 1001,		//查询标的证券
	TASK_QUERY_FinanceCredit = 1002,		//可融资信用查询

	TASK_QUERY_TicketCredit = 1003,		//可融券信用查询

	TASK_QUERY_FinanceAndTicketAmount = 1004,		//查询信用负债汇总(包括融资和融券负债)

	TASK_QUERY_FinanceList = 1005,		//融资明细查询

	TASK_QUERY_TicketList = 1006,		//融券明细查询

	TASK_QUERY_DebtList = 1007,		//负债流水查询

	TASK_QUERY_CreditStock = 1008,		//信用客户可转入担保证券查询

	TASK_QUERY_AssetLiability = 1009,		//资产负债查询

	TASK_QUERY_PawnTransition = 1010,		//担保物划转

	TASK_QUERY_DisPawnTransition = 1011,		//担保物划转撤单

	TASK_QUERY_MARGIN_DisEntrust = 1012,		//融资融券委托撤单

	TASK_QUERY_MarginRetMoney = 1013,		//直接还款

	TASK_QUERY_MarginRetStock = 1014,		//直接还券

	TASK_REQUEST_COMMON = 2000		//通用接口
};


enum PTK_ERRCODE
{
	PTKE_RISK = -100,		//风险不匹配
	PTKE_SUCCESS = 0,		// 成功
	PTKE_ERROR,				// 错误
	PTKE_OVERFLOW,			// 溢出
	PTKE_PARAM,				// 参数错误
	PTKE_RESOURCE,			// 资源不足
	PTKE_MEMORY,			// 内存不足
	PTKE_DLL_MISSING,		// dll文件丢失
	PTKE_API_INIT,			// API接口初始化失败
	PTKE_LOGIN,				// 登录失败
	PTKE_GATE_RESTORE,		// 网关重置
	PTKE_PASSWORD,			// 密码错误
	PTKE_NOTSUPPORTED,		// 不支持
	PTKE_NOTREADY,			// 未就绪
	PTKE_NOTEXIST,			// 目标不存在
	PTKE_NETWORK,			// 网络错误
	PTKE_ABORT,				// 操作被中止
	PTKE_TIMEOUT,			// 超时

	PTKE_VOLUMELIMIT = 30,	// 数量超过限制
	PTKE_CONTRACT,			// 合约不存在
	PTKE_REFPRICE,			// 参考价（对手价、挂单价、涨停价、跌停价等）为0
	PTKE_PRICE,				// 价格不正确
	PTKE_PRICELIMIT,		// 价格超过限制
	PTKE_OPENLIMIT,			// 开仓超过限制
	PTKE_LOSSLIMIT,			// 亏损超过限制
	PTKE_MARGINLIMIT,		// 保证金超过限制

	PTKE_MARKETCLOSED = 50,	// 未处于开盘状态
	PTKE_ALLTRADED,			// 委托已全部成交
};


enum PTK_PLATFORM		// 交易平台
{
	PPF_SFIT_F = 0,		// 上期技术期货
	PPF_JSD_F = 1,		// 金仕达期货
	PPF_HS_F = 2,		// 恒生期货
	PPF_DD_F = 3,		// 顶点期货
	PPF_JSD2_F = 4,		// 金仕达期货 V2
	PPF_HS2_F = 5,		// 恒生期货 V2
	//	PPF_JSDB2B_F	= 6,		//金仕达B2B接口
	PPF_SFIT_KS_F = 7,		//	金仕达仿CTP
	PPF_STANDARD_Future = 8,			//标准期货,连接标准网关

	PPF_LAST_F = 29,			// 

	PPF_START_S = 30,
	PPF_SFIT_S = 30,		// 上期技术股票
	PPF_SFIT_Q = 31,		// 上期技术股票期权
	PPF_SFIT_S2 = 32,		// 上期技术股票 CTP2柜台
	PPF_SFIT_Q2 = 33,		// 上期技术股票期权 CTP2柜台
	PPF_FCh_S = 34,		// 飞创股票现货
	PPF_FCh_Q = 35,		// 飞创股票期权
	PPF_STANDARD_S = 36,		//标准现货版
	PPF_STANDARD_Q = 37,		//标准期权版
	PPF_STANDARD_RZRQ = 38,	//标准融资融券版
	PPF_STANDARD_S_NEW = 39,	//股票采用新协议版
	PPF_STANDARD_Q_NEW = 40,		//标准期权版采用新协议版
	PPF_STANDARD_RZRQ_NEW = 41,	//标准融资融券版采用新协议版
	PPF_STANDARD_GOLD_NEW = 42,	//标准黄金新协议版
	PPF_STANDARD_GOLD = 43,		//标准黄金

	PPF_OES_S = 50,		//深圳通快速交易系统现货版
	PPF_LAST_S = 59,			// 

	PPF_PFHJ_F = 60,	// 浦发黄金
	PPF_JSDHJ_F = 61,	//金仕达黄金

	//100 -- 200 新协议 
	PPF_STADARD_TRADE = 100,		//新协议交易
	//201 -- 300 期货类
	PPF_SFIT_FUTURE = 201,			//上期技术期货
	PPF_KS_FUTURE = 202,		//金仕达B2C期货
	PPF_HSFUFX_FUTURE = 203,	//恒生UFX期货交易

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

// 交易任务
struct Task
{
	Task()
	{
		memset(this, 0, sizeof(*this));
		RequestNo = GenerateRequestNo();
	}
	// 提交任务的账号
	CAccountInfo Account;
	// 任务类型
	PTK_TASKTYPE uType;
	// 执行结果
	PTK_ERRCODE	 uResult;
	// 任务序号
	int iReqSn;
	// 请求的内部功能号
	int	funcno;
	// 用于请求时的序号
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