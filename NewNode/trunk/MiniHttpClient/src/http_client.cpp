#include "http_client.h"
#include <thread>
#include <iostream>
using namespace std;

// ��ʼ��client��̬����
int HttpClient::s_exit_flag = 0;
ReqCallback HttpClient::s_req_callback;
std::string result;
// �ͻ��˵�����������Ӧ
void HttpClient::OnHttpEvent(mg_connection *connection, int event_type, void *event_data)
{
	http_message *hm = (struct http_message *)event_data;
	int connect_status;

	switch (event_type)
	{
	case MG_EV_CONNECT:
		connect_status = *(int *)event_data;
		if (connect_status != 0)
		{
			printf("Error connecting to server, error code: %d\n", connect_status);
			s_exit_flag = 1;
		}
		break;
	case MG_EV_HTTP_REPLY:
	{
		//printf("Got reply:\n%.*s\n", (int)hm->body.len, hm->body.p);
		//std::string rsp = std::string(hm->body.p, hm->body.len);
		result = std::string(hm->body.p, hm->body.len);
		connection->flags |= MG_F_SEND_AND_CLOSE;
		s_exit_flag = 1; // ÿ���յ������رձ������ӣ����ñ��

		// �ص�����
		//cout << "OnHttpEvent threadid = " << std::this_thread::get_id() << endl;

		//s_req_callback(rsp);
	}
	break;
	case MG_EV_CLOSE:
		if (s_exit_flag == 0)
		{
			printf("Server closed connection\n");
			s_exit_flag = 1;
		};
		break;
	default:
		break;
	}
}


// ����һ�����󣬲��ص�����Ȼ��رձ�������
void HttpClient::SendReq(const std::string &url, ReqCallback req_callback)
{
	// ���ص�������ֵ
	s_exit_flag = 0;
	s_req_callback = req_callback;
	mg_mgr mgr;
	mg_mgr_init(&mgr, NULL);
	auto connection = mg_connect_http(&mgr, OnHttpEvent, url.c_str(), NULL, NULL);

//	mg_set_protocol_http_websocket(connection);

	printf("Send http request %s\n", url.c_str());

	// loop
	while (s_exit_flag == 0)
		mg_mgr_poll(&mgr, 500);

	mg_mgr_free(&mgr);
}

void HttpClient::SendReqNoCallback(const std::string &url)
{
	s_exit_flag = 0;
	mg_mgr mgr;
	mg_mgr_init(&mgr, NULL);
	auto connection = mg_connect_http(&mgr, OnHttpEvent, url.c_str(), NULL, NULL);
	printf("Send http request %s\n", url.c_str());
	// loop
	while (s_exit_flag == 0)
		mg_mgr_poll(&mgr, 50);

	cout << result.c_str() << endl;
}