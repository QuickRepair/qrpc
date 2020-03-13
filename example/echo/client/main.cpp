#include "server/Server.h"
#include "example/echo/msg/ServiceGen.h"
#include "example/echo/msg/MsgGen.h"
#include <iostream>
#include <stdexcept>

using std::make_unique;
using std::runtime_error;

int main()
{
	try
	{
		Stub stub(make_unique<qrpc::Connection>("127.0.0.1", 6743));
		std::cout << "client start" << std::endl;

		for (char i = 0; i < 10; ++i)
		{
			EchoCharRequest request;
			request.setMsg('0' + i);
			EchoCharResponse response;
			stub.echo(&request, &response);
			std::cout << response.getMsg() << std::endl;
		}

		for (char i = 0; i < 100; ++i)
		{
			EchoRequestSample request;
			request.setMsg("echo" + std::to_string(i));
			EchoResponseSample response;
			stub.echoSample(&request, &response);
			std::cout << response.getMsg() << std::endl;
		}
	}
	catch (std::runtime_error &e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
