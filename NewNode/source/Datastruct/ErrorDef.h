#if !defined(__COMM_D_ERROR_CODE_INCLUDED_)
#define __COMM_D_ERROR_CODE_INCLUDED_

enum SELECT_TYPE //检测类型
{
	SELECT_READ		= 0x01,  //可读检测
	SELECT_WRITE,			//可写检测
	SELECT_EXCEPTION,		//异常检测
	SELECT_READ_WRITE,		//读写检测
	SELECT_OTHER			//所有检测
};

//套接字的select结果。可以组合使用
#define COM_NO_STAT				0x00000000
#define COM_READ				0x00000001
#define COM_WRITE				0x00000010
#define COM_EXCEPTION			0x00000100

#define COM_SUCESS				0
#define PROXY_SUCCESS			0
#define COM_NEW_ERR					-1	//new错误
#define COM_NO_INIT					-2	//没有初始化
#define COM_INITING					-3	//正在初始化
#define COM_EXIT					-4	//正在退出
#define COM_LEN_ERR					-5  //数据长度不合法
#define COM_NO_POS					-6	//没有找到对应的空闲位子
#define INVALID_SVRADDR				-7	//地址不正确
#define DOCONNECT_FAILED			-8	//连接错误
#define PROXYE_REQUESTFAILED		-9	//向代理服务器发送请求失败
#define PROXYE_WAITFORANWSER		-10	//正在等待proxy的应答
#define SRV_GRACECLOSE				-11	//服务器温和关闭	
#define PROXYE_AUTHREQUIRED			-12 //代理服务器身份认证失败
#define PROXYE_AUTHTYPEUNKNOWN		-13	//未知的用户验证类型
#define PROXYE_AUTHNOLOGON			-14	//代理服务器需要身份认证
#define PROXYE_AUTHFAILED			-15	//代理服务器用户验证不成功
#define COM_SETOPT_ERR				-16	//套接字设置属性错误
#define COM_ERR						-17 //通讯错误
#define COM_TIMEOUT					-18 //通讯超时
#define COM_CERTLOADERR				-19 //证书系统导入错误
#define COM_SOCKET_INVALID			-20	//套接字无效
#define COM_SSL_INVALID				-21 //SSL没有初始化
#define COM_SSL_NEW_ERR				-22 //新建SSL错误
#define COM_SSL_OTHER_ERR			-23 //SSL其他错误

#endif
