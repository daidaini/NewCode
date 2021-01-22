#if !defined(__COMM_D_ERROR_CODE_INCLUDED_)
#define __COMM_D_ERROR_CODE_INCLUDED_

enum SELECT_TYPE //�������
{
	SELECT_READ		= 0x01,  //�ɶ����
	SELECT_WRITE,			//��д���
	SELECT_EXCEPTION,		//�쳣���
	SELECT_READ_WRITE,		//��д���
	SELECT_OTHER			//���м��
};

//�׽��ֵ�select������������ʹ��
#define COM_NO_STAT				0x00000000
#define COM_READ				0x00000001
#define COM_WRITE				0x00000010
#define COM_EXCEPTION			0x00000100

#define COM_SUCESS				0
#define PROXY_SUCCESS			0
#define COM_NEW_ERR					-1	//new����
#define COM_NO_INIT					-2	//û�г�ʼ��
#define COM_INITING					-3	//���ڳ�ʼ��
#define COM_EXIT					-4	//�����˳�
#define COM_LEN_ERR					-5  //���ݳ��Ȳ��Ϸ�
#define COM_NO_POS					-6	//û���ҵ���Ӧ�Ŀ���λ��
#define INVALID_SVRADDR				-7	//��ַ����ȷ
#define DOCONNECT_FAILED			-8	//���Ӵ���
#define PROXYE_REQUESTFAILED		-9	//������������������ʧ��
#define PROXYE_WAITFORANWSER		-10	//���ڵȴ�proxy��Ӧ��
#define SRV_GRACECLOSE				-11	//�������º͹ر�	
#define PROXYE_AUTHREQUIRED			-12 //��������������֤ʧ��
#define PROXYE_AUTHTYPEUNKNOWN		-13	//δ֪���û���֤����
#define PROXYE_AUTHNOLOGON			-14	//�����������Ҫ�����֤
#define PROXYE_AUTHFAILED			-15	//����������û���֤���ɹ�
#define COM_SETOPT_ERR				-16	//�׽����������Դ���
#define COM_ERR						-17 //ͨѶ����
#define COM_TIMEOUT					-18 //ͨѶ��ʱ
#define COM_CERTLOADERR				-19 //֤��ϵͳ�������
#define COM_SOCKET_INVALID			-20	//�׽�����Ч
#define COM_SSL_INVALID				-21 //SSLû�г�ʼ��
#define COM_SSL_NEW_ERR				-22 //�½�SSL����
#define COM_SSL_OTHER_ERR			-23 //SSL��������

#endif
