#pragma once

#include "mongoose.h"

#include <string.h>
#include <functional>
#include <string>
#include <unordered_map>
#include <unordered_set>


using OnRspCallback = std::function<void(mg_connection *, std::string)>;

using ReqHandler = std::function<bool(std::string, std::string, mg_connection *c, OnRspCallback)>;

class CHttpServer
{
public:
	CHttpServer() = default;
	~CHttpServer() = default;

	void Init(const std::string& port);

	bool Start();

	void Close();

	//ע��ص����¼���������
	void RegisterHandler(const std::string &url, ReqHandler req_handler);
	//ע���ص�
	void UnregisterHandler(const std::string &url);

public:
	//web����ѡ��
	static mg_serve_http_opts m_ServerOption;
	//��ҳ��Ŀ¼
	static std::string m_WebDir;
	//�ص�����ӳ���
	static std::unordered_map<std::string, ReqHandler> m_HandlerMap;

private:
	//��̬�¼���Ӧ����
	static void OnHttpWebSocketEvent(mg_connection *connection, int event_type, void* event_data);

	//����http�¼�
	static void HandleHttpEvent(mg_connection *connection, http_message *http_req);
	static void SendHttpRsp(mg_connection *connection, std::string rsp);

	//����websocket��Ϣ
	static void HandleWebsocketMessage(mg_connection *connection, int event_type, websocket_message *ws_msg);
	//������Ϣ��ָ������
	static void SendWebsocketMsg(mg_connection *connection, std::string msg);
	//�ж��Ƿ���websocket��������
	static int IsWebsocket(const mg_connection *connection);
	//���������ӹ㲥��Ϣ
	static void BroadcastWebsocketMsg(std::string msg);

private:
	std::string m_Port;

	//���ӹ�����
	mg_mgr m_Manager;

	//����websocket����
	static std::unordered_set<mg_connection*> m_WebsocketSessionSet;
};