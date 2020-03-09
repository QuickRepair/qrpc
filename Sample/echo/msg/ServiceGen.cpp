//
// Created by gaojian on 2019/12/27.
//

#include "ServiceGen.h"
#include "MsgGen.h"
#include "CodeGen/MethodWrapper.h"
#include "Client/Call.h"
#include <memory>

using std::make_unique;

Service::Service()
{
	registerService(
			std::move(make_unique<qrpc::RpcMethodHandler<Service, EchoCharRequest, EchoCharResponse>>(std::mem_fn(&Service::echo), this)),
			EchoTag
			);
	registerService(
			std::move(make_unique<qrpc::RpcMethodHandler<Service, EchoRequestSample, EchoResponseSample>>(std::mem_fn(&Service::echoSample), this)),
			EchoSampleTag
	);
}

void Service::echo(EchoCharRequest *request, EchoCharResponse *response)
{
	response->setMsg(request->getMsg());
}

void Service::echoSample(EchoRequestSample *request, EchoResponseSample *response)
{
	response->setMsg(request->getMsg());
}

Stub::Stub(std::unique_ptr<qrpc::Connection> &&connection)
	: m_connection{std::move(connection)}, m_callMethod{make_unique<qrpc::BlockingCall>(m_connection.get())}
{}

void Stub::echo(EchoCharRequest *request, EchoCharResponse *response)
{
	m_callMethod->call(EchoTag, request, response);
}

void Stub::echoSample(EchoRequestSample *request, EchoResponseSample *response)
{
	m_callMethod->call(EchoSampleTag, request, response);
}