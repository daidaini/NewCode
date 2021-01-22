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

	//注册回调（事件处理）函数
	void RegisterHandler(const std::string &url, ReqHandler req_handler);
	//注销回调
	void UnregisterHandler(const std::string &url);

public:
	//web服务选项
	static mg_serve_http_opts m_ServerOption;
	//网页根目录
	static std::string m_WebDir;
	//回调函数映射表
	static std::unordered_map<std::string, ReqHandler> m_HandlerMap;

private:
	//静态事件响应函数
	static void OnHttpWebSocketEvent(mg_connection *connection, int event_type, void* event_data);

	//处理http事件
	static void HandleHttpEvent(mg_connection *connection, http_message *http_req);
	static void SendHttpRsp(mg_connection *connection, std::string rsp);

	//处理websocket消息
	static void HandleWebsocketMessage(mg_connection *connection, int event_type, websocket_message *ws_msg);
	//发送消息到指定连接
	static void SendWebsocketMsg(mg_connection *connection, std::string msg);
	//判断是否是websocket类型连接
	static int IsWebsocket(const mg_connection *connection);
	//给所有连接广播消息
	static void BroadcastWebsocketMsg(std::string msg);

private:
	std::string m_Port;

	//连接管理器
	mg_mgr m_Manager;

	//缓存websocket连接
	static std::unordered_set<mg_connection*> m_WebsocketSessionSet;
};