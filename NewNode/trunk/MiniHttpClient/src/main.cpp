#include <iostream>
#include <future>
#include "http_client.h"

void handle_func(std::string rsp)
{
	// do sth according to rsp
	std::cout << "http rsp1: " << rsp << std::endl;
}

void GetCalcResult(double x, double y)
{
	std::string url2 = "http://127.0.0.1:20002/api/sum";
	std::string param = "n1=" + std::to_string(x) + "&n2=" + std::to_string(y);
	
	std::string requests = url2 + "?" + param;

	/*HttpClient::SendReq(requests, [](std::string rsp)
	{
		std::cout << "GetCalcResult: " << rsp << std::endl;
	});*/

	HttpClient::SendReqNoCallback(requests);
}

int main()
{
	

	for (int i = 0; i < 1; i++)
	{
		//std::async(std::launch::async, GetCalcResult, i + 1.0, i + 2.1);
		//std::async(std::launch::async, GetCalcResult, i + 1.1, i + 2.2);
		
		GetCalcResult(i + 1.0, i + 2.1);
		
		//GetCalcResult(i + 1.1, i + 2.2);
		/*GetCalcResult(i + 1.2, i + 2.3);
		GetCalcResult(i + 1.3, i + 2.4);
		GetCalcResult(i + 1.5, i + 2.5);*/
	}

	system("pause");
	return 0;
}

//int main()
//{
//	// 拼完整url，带参数，暂时只写了GET请求
////	std::string url1 = "http://127.0.0.1:7999/api/hello";
////	HttpClient::SendReq(url1, handle_func);
//
//	std::string url2 = "http://101.226.207.176:20002/api/sum";
//	std::string param = "n1=0.1&n2=13.44";
//	std::string requests = url2 + "?" + param;
//	HttpClient::SendReq(requests, [](std::string rsp) {
//		std::cout << "http rsp2: " << rsp << std::endl;
//	});
//
//	system("pause");
//
//	return 0;
//}