#include "server/Server.h"
#include "example/echo/msg/ServiceGen.h"
#include "example/echo/msg/MsgGen.h"
#include <iostream>

using std::make_unique;			using std::runtime_error;

int main()
{
	qrpc::Server server("0.0.0.0", 6743);
	server.registerService(make_unique<Service>());
	auto msgRepository = make_unique<qrpc::MsgRepository>();
	msgRepository->addCreator(make_unique<qrpc::RpcMessageCreator<EchoCharRequest>>(&EchoCharRequest::create), EchoCharRequest::tag);
	msgRepository->addCreator(make_unique<qrpc::RpcMessageCreator<EchoCharResponse>>(&EchoCharResponse::create), EchoCharResponse::tag);
	msgRepository->registerServiceTagPair(Service::EchoTag, EchoCharRequest::tag, EchoCharResponse::tag);

	msgRepository->addCreator(make_unique<qrpc::RpcMessageCreator<EchoRequestSample>>(&EchoRequestSample::create), EchoRequestSample::tag);
	msgRepository->addCreator(make_unique<qrpc::RpcMessageCreator<EchoResponseSample>>(&EchoResponseSample::create), EchoResponseSample::tag);
	msgRepository->registerServiceTagPair(Service::EchoSampleTag, EchoRequestSample::tag, EchoResponseSample::tag);

	server.registerMsgRepository(std::move(msgRepository));

	std::cout << "server start" << std::endl;
	server.waitAndHandleMsg();
}
