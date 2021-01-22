#ifndef DATA_TYPE_H
#define DATA_TYPE_H

#include "UFDataType.h"
#include <limits>

#define INT_NULL_VAL INT_MAX
#define MAX_SINGLE_MESSAGE_LENGTH 1024 * 64

typedef char AccountIDType[64];	//�ʽ��˺�����
typedef char ClientIDType[32];	//�ͻ�������
typedef char LoginAccountIDType[64];	//��¼�˺�����
typedef char IpType[64];	//IP����
typedef char MacType[64];	//Mac����
typedef char HddType[64];	//Ӳ�̱������
typedef char AppIDType[32];	//AppID����
typedef char VersionType[64];	//�汾������
typedef char PhoneNumberType[20];	//�ֻ���������


//��¼���
enum class LoginTypeEnum
{
	//֤ȯ
	Stock = 0,
	//������ȯ
	Margin = 5,
	//������Ȩ
	Option = 6,
	//�ƽ�
	Gold = 7,
	//�ڻ�
	Future = 8,
	//����
	OutsideTrade = 9,
	//��Ʒ�ֻ�
	Commodity = 10,
	//��ת����
	Transfer = 101,
	//����Ա
	Manage = 102,
	//��ֵ
	None = INT_NULL_VAL
};

//ƽ̨
enum class PlatformEnum
{
	//windows
	Windows = 1,
	//IOS
	IOS = 2,
	//��׿
	ANDROID = 3,
	//Web
	Web = 4,
	//Linux
	Linux = 5,
	//��ֵ
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

//�˺�״̬
enum class AccountStatusEnum
{
	//����
	Normal = 0,
	//�쳣
	Abnormal = 1,
};

//�ϴ�������
enum class UploadPackageTypeEnum
{
	Request = 0,
	Response = 1,
};

enum class AccountTypeEnum : char
{
	//�ͻ���
	ClientID = 'a',
	//�ʽ��˺�
	AccountID = '0'
};

enum class TradeClassifyEnum : char
{
	//Ͷ��
	Speculation = '1',
	//����
	Arbitrage = '2', 
	//��ֵ
	Hedge = '3'
};

enum class MoneyTypeEnum : char
{
	//δ֪
	Unkown = 'x',
	//�����
	RMB = '0',
	//��Ԫ
	USD = '1',
	//�۱�
	HKD = '2'
};

enum class BsTypeEnum : char
{
	Unknown = 0,
	Buy = '0',
	Sell = '1',
	//ETF�깺
	Sub = '2',
	//ETF���
	Red = '3',
	//���ڻ����깺
	LOFSub = '4',
	//���ڻ������
	LOFRed = '5',
	//���ڻ����Ϲ�
	LOFBuy = '6',
	//������
	FundSplit = '7',
	//����ϲ�
	FundMerge = '8',
	//����ת��
	FundTransfer = '9',
	//ETF�ֽ��Ϲ�
	FundCashSub = 'A',
	//ETF��Ʊ�Ϲ�
	FundStockSub = 'B',
	//���ع�
	BuyBackPositive = 'C',
	//��ع�
	BuyBackReserve = 'D',
	//�¹��깺
	Apply = 'E',
	//�̺󶨼���
	BuyAfterMarket = 'F',
	//�̺󶨼���
	SellAfterMarket = 'G',
	//���
	RationShare = 'H',
};

enum class OrderStatusEnum : char
{
	//δ֪
	UnKnown = 'x', 
	//�����걨
	Inserting = '0',
	//���걨
	Inserted = '1',
	//���ֳɽ�
	PartTraded = '2',
	//�ѳɽ�
	AllTraded = '3',
	//�ѳ���
	Canceled = '4',
	//���ɲ���
	PartTradedCacneled = '5',
	//������
	Cancelling = '6',
	//����
	Modifying = '8',
	//�ϵ�
	Error = 'e',
	//�ѹ���
	Halted = 'h'
};

class MarketIDEnum
{
public:
	typedef UFStringType<8> Type;

	//�Ϻ���Ȩ
	static const Type SHQQ;
	//������Ȩ
	static const Type SZQQ;
	//�Ϻ���ƱA��
	static const Type SHGP;
	//���ڹ�ƱA��
	static const Type SZGP;
	//�Ϻ���ƱB��
	static const Type SHGP_B;
	//���ڹ�ƱB��
	static const Type SZGP_B;
};

class CombineCodeEnum
{
public:
	typedef UFStringType<8> Type;
	//�Ϲ�ţ�м۲����
	static const Type CNSJC;
	//�Ϲ�ţ�м۲����
	static const Type PNSJC;
	//�Ϲ����м۲����
	static const Type CXSJC;
	//�Ϲ����м۲����
	static const Type PXSJC;
	//��ʽ��ͷ���
	static const Type KS;
	//���ʽ��ͷ���
	static const Type KKS;
	//�Ϲ���Ȩ�Ǳ���ת����
	static const Type ZBD;
	//�Ϲ���Ȩ���ҿ���ת��֤�𿪲�
	static const Type ZXJ;
};


#endif
