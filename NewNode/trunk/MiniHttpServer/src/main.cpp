#include "http_sever.h"

#include <iostream>
#include <memory>
using namespace std;


bool handle_fun1(std::string url, std::string body, mg_connection *c, OnRspCallback rsp_callback)
{
	// do sth
	std::cout << "handle fun1" << std::endl;
	std::cout << "url: " << url << std::endl;
	std::cout << "body: " << body << std::endl;

	rsp_callback(c, "rsp1");

	return true;
}

bool handle_fun2(std::string url, std::string body, mg_connection *c, OnRspCallback rsp_callback)
{
	// do sth
	std::cout << "handle fun2" << std::endl;
	std::cout << "url: " << url << std::endl;
	std::cout << "body: " << body << std::endl;

	rsp_callback(c, "rsp2");

	return true;
}


int main()
{
	string port = "7999";
	auto http_server = std::shared_ptr<CHttpServer>(new CHttpServer);

	http_server->Init(port);

	http_server->RegisterHandler("/api/fun1", handle_fun1);
	http_server->RegisterHandler("/api/fun2", handle_fun2);
	http_server->Start();

	return 0;
}