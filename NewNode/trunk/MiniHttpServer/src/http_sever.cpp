#include "http_sever.h"

std::string CHttpServer::m_WebDir = "./web";
mg_serve_http_opts CHttpServer::m_ServerOption;
std::unordered_map<std::string, ReqHandler> CHttpServer::m_HandlerMap;
std::unordered_set<mg_connection*> CHttpServer::m_WebsocketSessionSet;

void CHttpServer::Init(const std::string& port)
{
	m_Port = port;

	m_ServerOption.enable_directory_listing = "yes";
	m_ServerOption.document_root = m_WebDir.c_str();
}

bool CHttpServer::Start()
{
	mg_mgr_init(&m_Manager, nullptr);

	mg_connection * conn = mg_bind(&m_Manager, m_Port.c_str(), CHttpServer::OnHttpWebSocketEvent);
	if (conn == nullptr)
		return false;

	//for both http and websocket
	mg_set_protocol_http_websocket(conn);

	printf("Starting http server at port: %s\n", m_Port.c_str());

	while (true)
	{
		mg_mgr_poll(&m_Manager, 500);	//ms
	}
}

void CHttpServer::Close()
{
	mg_mgr_free(&m_Manager);
}

void CHttpServer::RegisterHandler(const std::string &url, ReqHandler req_handler)
{
	if (m_HandlerMap.find(url) == m_HandlerMap.end())
	{
		m_HandlerMap.emplace(url, req_handler);
	}
}

void CHttpServer::UnregisterHandler(const std::string &url)
{
	auto it = m_HandlerMap.find(url);
	if (it != m_HandlerMap.end())
	{
		m_HandlerMap.erase(it);
	}
}

void CHttpServer::OnHttpWebSocketEvent(mg_connection *connection, int event_type, void* event_data)
{
	//区分http 和 websocket
	if (event_type == MG_EV_HTTP_REQUEST)
	{
		http_message *http_req = (http_message*)event_data;
		HandleHttpEvent(connection, http_req);
	}
	else if (event_type == MG_EV_WEBSOCKET_HANDSHAKE_DONE ||
		event_type == MG_EV_WEBSOCKET_FRAME ||
		event_type == MG_EV_CLOSE)
	{
		websocket_message *ws_message = (struct websocket_message *)event_data;
		HandleWebsocketMessage(connection, event_type, ws_message);
	}
}


static bool route_check(http_message *http_msg, char *route_prefix)
{
	if (mg_vcmp(&http_msg->uri, route_prefix) == 0)
	{
		return true;
	}
	else 
		return false;
}

void CHttpServer::HandleHttpEvent(mg_connection *connection, http_message *http_req)
{
	std::string req_str = std::string(http_req->message.p, http_req->uri.len);
	printf("Got request : %s\n", req_str.c_str());

	//看是否注册过回调
	std::string url = std::string(http_req->uri.p, http_req->uri.len);
	std::string body = std::string(http_req->body.p, http_req->body.len);
	auto it = m_HandlerMap.find(url);
	if (it != m_HandlerMap.end())
	{
		ReqHandler handle_func = it->second;
		handle_func(url, body, connection, &CHttpServer::SendHttpRsp);
	}

	if (route_check(http_req, "/"))	//index page
	{
		mg_serve_http(connection, http_req, m_ServerOption);
	}
	else if (route_check(http_req, "/api/hello"))
	{
		//直接回传
		SendHttpRsp(connection, "Welcome to httpserver");
	}
	else if (route_check(http_req, "/api/sum"))
	{
		//简单post请求，加法运算测试
		char n1[100], n2[100];
		//get from variables
		/*获取请求参数，get请求从query_string中获取；post请求从body中获取
		*/
		if (::strnicmp(http_req->method.p, "GET",3) == 0)
		{
			mg_get_http_var(&http_req->query_string, "n1", n1, sizeof(n1));
			mg_get_http_var(&http_req->query_string, "n2", n2, sizeof(n2));
		}
		else
		{
			mg_get_http_var(&http_req->body, "n1", n1, sizeof(n1));
			mg_get_http_var(&http_req->body, "n2", n2, sizeof(n2));
		}

		double result = strtod(n1, NULL) + strtod(n2, NULL);
		SendHttpRsp(connection, std::to_string(result));
	}
	else
	{
		mg_printf(connection, "%s",
			"HTTP/1.1 501 Not Implemented\r\n"
			"Content-Length: 0\r\n\r\n");
	}
}

void CHttpServer::SendHttpRsp(mg_connection *connection, std::string rsp)
{
	// --- 未开启CORS
	// 必须先发送header, 暂时还不能用HTTP/2.0

	mg_printf(connection, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
	// 以json形式返回
	mg_printf_http_chunk(connection, "{ \"result\": %s }", rsp.c_str());
	// 发送空白字符快，结束当前响应
	mg_send_http_chunk(connection, "", 0);

	// --- 开启CORS
	/*mg_printf(connection, "HTTP/1.1 200 OK\r\n"
	"Content-Type: text/plain\n"
	"Cache-Control: no-cache\n"
	"Content-Length: %d\n"
	"Access-Control-Allow-Origin: *\n\n"
	"%s\n", rsp.length(), rsp.c_str()); */

}

void CHttpServer::HandleWebsocketMessage(mg_connection *connection, int event_type, websocket_message *ws_msg)
{
	if (event_type == MG_EV_WEBSOCKET_HANDSHAKE_DONE)
	{
		printf("client websocket connected\n");
		// 获取连接客户端的IP和端口
		char addr[32];
		mg_sock_addr_to_str(&connection->sa, addr, sizeof(addr), MG_SOCK_STRINGIFY_IP | MG_SOCK_STRINGIFY_PORT);
		printf("client addr: %s\n", addr);

		//添加session
		m_WebsocketSessionSet.emplace(connection);

		SendWebsocketMsg(connection, "client websocket connected");
	}
	else if (event_type == MG_EV_WEBSOCKET_FRAME)
	{
		mg_str received_msg = {
			(char*)ws_msg->data, ws_msg->size
		};

		char buff[1024] = { 0 };
		strncpy(buff, received_msg.p, received_msg.len);

		printf("receieved msg: %s\n", buff);
		SendWebsocketMsg(connection, "send your msg back: " + std::string(buff));
		//BroadcastWebsocketMsg("broadcast msg: " + std::string(buff));
	}
	else if (event_type == MG_EV_CLOSE)
	{
		if (IsWebsocket(connection))
		{
			printf("client websocket closed\n");
			//移除session
			auto it = m_WebsocketSessionSet.find(connection);
			if (it != m_WebsocketSessionSet.end())
				m_WebsocketSessionSet.erase(it);
		}
	}
}

void CHttpServer::SendWebsocketMsg(mg_connection *connection, std::string msg)
{
	mg_send_websocket_frame(connection, WEBSOCKET_OP_TEXT, msg.c_str(), msg.length());
}

int CHttpServer::IsWebsocket(const mg_connection *connection)
{
	return connection->flags & MG_F_IS_WEBSOCKET;
}

void CHttpServer::BroadcastWebsocketMsg(std::string msg)
{
	for (mg_connection * conn : m_WebsocketSessionSet)
	{
		mg_send_websocket_frame(conn, WEBSOCKET_OP_TEXT, msg.c_str(), msg.length());
	}
}
