#include "server/Server.h"
#include "test_message.h"
#include "test_service.h"
#include <iostream>

using std::make_unique;			using std::runtime_error;

class ServiceImpl final : public Service {
public:
	void echo(EchoCharRequest *request, EchoCharResponse *response) override
	{
		response->set_varname(request->get_varname());
	}
	void echoSample(EchoRequestSample *request, EchoResponseSample *response) override
	{
		response->set_varname(request->get_varname());
	}
};

int main()
{
	qrpc::Server server("0.0.0.0", 6743);
	server.registerService(make_unique<ServiceImpl>());
	auto msgRepository = make_unique<qrpc::MsgRepository>();
	msgRepository->addCreator(make_unique<qrpc::RpcMessageCreator<EchoCharRequest>>(&EchoCharRequest::create), EchoCharRequest::tag);
	msgRepository->addCreator(make_unique<qrpc::RpcMessageCreator<EchoCharResponse>>(&EchoCharResponse::create), EchoCharResponse::tag);
	msgRepository->registerServiceTagPair(Service::echoTag, EchoCharRequest::tag, EchoCharResponse::tag);

	msgRepository->addCreator(make_unique<qrpc::RpcMessageCreator<EchoRequestSample>>(&EchoRequestSample::create), EchoRequestSample::tag);
	msgRepository->addCreator(make_unique<qrpc::RpcMessageCreator<EchoResponseSample>>(&EchoResponseSample::create), EchoResponseSample::tag);
	msgRepository->registerServiceTagPair(Service::echoSampleTag, EchoRequestSample::tag, EchoResponseSample::tag);

	server.registerMsgRepository(std::move(msgRepository));

	std::cout << "server start" << std::endl;
	server.waitAndHandleMsg();
}
