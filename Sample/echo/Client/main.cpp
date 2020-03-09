#include "Server/Server.h"
#include "Sample/echo/msg/ServiceGen.h"
#include "Sample/echo/msg/MsgGen.h"
#include <iostream>
#include <stdexcept>

using std::make_unique;
using std::runtime_error;

int main()
{
	try
	{
		Stub stub(make_unique<qrpc::Connection>("127.0.0.1", 67431));
		std::cout << "client start" << std::endl;

		for (char i = 0; i < 10; ++i)
		{
			EchoRequest request;
			request.setMsg('0' + i);
			EchoResponse response;
			stub.echo(&request, &response);
			std::cout << response.getMsg() << std::endl;
		}

		for (char i = 'a'; i < 'z'; ++i)
		{
			EchoRequestSample request1;
			request1.setMsg(i);
			EchoResponseSample response1;
			stub.echoSample(&request1, &response1);
			std::cout << response1.getMsg() << std::endl;
		}
	}
	catch (std::runtime_error &e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
