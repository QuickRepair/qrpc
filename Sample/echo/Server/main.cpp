#include "Server/Server.h"
#include "Sample/echo/msg/ServiceGen.h"
#include "Sample/echo/msg/MsgGen.h"
#include "CodeGen/MethodWrapper.h"
#include <iostream>
#include <stdexcept>

using std::make_unique;			using std::runtime_error;

int main()
{
	qrpc::Server server("0.0.0.0", 67431);
	server.registerService(make_unique<Service>());
	auto msgRepository = make_unique<qrpc::MsgRepository>();
	msgRepository->addCreator(make_unique<qrpc::RpcMessageCreator<EchoRequest>>(&EchoRequest::create), EchoRequest::tag);
	msgRepository->addCreator(make_unique<qrpc::RpcMessageCreator<EchoResponse>>(&EchoResponse::create), EchoResponse::tag);
	msgRepository->registerServiceTagPair(Service::EchoTag, Service::EchoRequestTag, Service::EchoResponseTag);

	msgRepository->addCreator(make_unique<qrpc::RpcMessageCreator<EchoRequestSample>>(&EchoRequestSample::create), EchoRequestSample::tag);
	msgRepository->addCreator(make_unique<qrpc::RpcMessageCreator<EchoResponseSample>>(&EchoResponseSample::create), EchoResponseSample::tag);
	msgRepository->registerServiceTagPair(Service::EchoSampleTag, Service::EchoRequestSampleTag, Service::EchoResponseSampleTag);

	server.registerMsgRepository(std::move(msgRepository));

	std::cout << "server start" << std::endl;
	while (true)
		server.waitAndHandleMsg();
}
