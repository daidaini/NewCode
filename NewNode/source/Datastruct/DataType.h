#ifndef DATA_TYPE_H
#define DATA_TYPE_H

#include "UFDataType.h"
#include <limits>

#define INT_NULL_VAL INT_MAX
#define MAX_SINGLE_MESSAGE_LENGTH 1024 * 64

typedef char AccountIDType[64];	//资金账号类型
typedef char ClientIDType[32];	//客户号类型
typedef char LoginAccountIDType[64];	//登录账号类型
typedef char IpType[64];	//IP类型
typedef char MacType[64];	//Mac类型
typedef char HddType[64];	//硬盘编号类型
typedef char AppIDType[32];	//AppID类型
typedef char VersionType[64];	//版本号类型
typedef char PhoneNumberType[20];	//手机号码类型


//登录类别
enum class LoginTypeEnum
{
	//证券
	Stock = 0,
	//融资融券
	Margin = 5,
	//个股期权
	Option = 6,
	//黄金
	Gold = 7,
	//期货
	Future = 8,
	//外盘
	OutsideTrade = 9,
	//商品现货
	Commodity = 10,
	//中转服务
	Transfer = 101,
	//管理员
	Manage = 102,
	//空值
	None = INT_NULL_VAL
};

//平台
enum class PlatformEnum
{
	//windows
	Windows = 1,
	//IOS
	IOS = 2,
	//安卓
	ANDROID = 3,
	//Web
	Web = 4,
	//Linux
	Linux = 5,
	//空值
	None = INT_NULL_VAL
};
#define PTK_PF_MAX static_cast<int>(PlatformEnum::Linux)
inline bool IsValidPlatForm(PlatformEnum platform)
{
	return platform == PlatformEnum::Windows ||
		platform == PlatformEnum::IOS ||
		platform == PlatformEnum::ANDROID ||
		platform == PlatformEnum::Web ||
		platform == PlatformEnum::Linux;
}

enum class ProductEnum
{
	All = INT_NULL_VAL,
	Gate = 0,
	HD = 1,
	SDS = 2,
	SDW = 3,
	MPFuture = 4,
	MPStock = 5,
	MPOption = 7,
	MP = 8,
	JZT = 9,
	ZSCF = 10,
	Pobo6 = 11,
	Cloud = 12,
	Web = 14,
	MPMargin = 15,
	Quant = 16,
	TLW = 17,
	OptionPobo6 = 18,
	HongKongPobo6 = 19,
	PrivatePobo6 = 20,
	ManagePobo6 = 21,
	TradeMonitor = 22
};

//账号状态
enum class AccountStatusEnum
{
	//正常
	Normal = 0,
	//异常
	Abnormal = 1,
};

//上传包类型
enum class UploadPackageTypeEnum
{
	Request = 0,
	Response = 1,
};

enum class AccountTypeEnum : char
{
	//客户号
	ClientID = 'a',
	//资金账号
	AccountID = '0'
};

enum class TradeClassifyEnum : char
{
	//投机
	Speculation = '1',
	//套利
	Arbitrage = '2', 
	//保值
	Hedge = '3'
};

enum class MoneyTypeEnum : char
{
	//未知
	Unkown = 'x',
	//人民币
	RMB = '0',
	//美元
	USD = '1',
	//港币
	HKD = '2'
};

enum class BsTypeEnum : char
{
	Unknown = 0,
	Buy = '0',
	Sell = '1',
	//ETF申购
	Sub = '2',
	//ETF赎回
	Red = '3',
	//场内基金申购
	LOFSub = '4',
	//场内基金赎回
	LOFRed = '5',
	//场内基金认购
	LOFBuy = '6',
	//基金拆分
	FundSplit = '7',
	//基金合并
	FundMerge = '8',
	//基金转换
	FundTransfer = '9',
	//ETF现金认购
	FundCashSub = 'A',
	//ETF股票认购
	FundStockSub = 'B',
	//正回购
	BuyBackPositive = 'C',
	//逆回购
	BuyBackReserve = 'D',
	//新股申购
	Apply = 'E',
	//盘后定价买
	BuyAfterMarket = 'F',
	//盘后定价卖
	SellAfterMarket = 'G',
	//配股
	RationShare = 'H',
};

enum class OrderStatusEnum : char
{
	//未知
	UnKnown = 'x', 
	//正在申报
	Inserting = '0',
	//已申报
	Inserted = '1',
	//部分成交
	PartTraded = '2',
	//已成交
	AllTraded = '3',
	//已撤单
	Canceled = '4',
	//部成部撤
	PartTradedCacneled = '5',
	//待撤单
	Cancelling = '6',
	//待改
	Modifying = '8',
	//废单
	Error = 'e',
	//已挂起
	Halted = 'h'
};

class MarketIDEnum
{
public:
	typedef UFStringType<8> Type;

	//上海期权
	static const Type SHQQ;
	//深圳期权
	static const Type SZQQ;
	//上海股票A股
	static const Type SHGP;
	//深圳股票A股
	static const Type SZGP;
	//上海股票B股
	static const Type SHGP_B;
	//深圳股票B股
	static const Type SZGP_B;
};

class CombineCodeEnum
{
public:
	typedef UFStringType<8> Type;
	//认购牛市价差策略
	static const Type CNSJC;
	//认沽牛市价差策略
	static const Type PNSJC;
	//认购熊市价差策略
	static const Type CXSJC;
	//认沽熊市价差策略
	static const Type PXSJC;
	//跨式空头组合
	static const Type KS;
	//宽跨式空头组合
	static const Type KKS;
	//认购期权非备兑转备兑
	static const Type ZBD;
	//认购期权备兑开仓转保证金开仓
	static const Type ZXJ;
};


#endif
