//
// Created by gaojian on 2019/12/27.
//

#ifndef SERVICE_H
#define SERVICE_H

#include "CodeGen/Service.h"
#include "Client/Call.h"
#include "Client/Connection.h"
#include "MsgGen.h"

class EchoRequest;
class EchoResponse;

class Service : public qrpc::Service {
public:
	Service();
	~Service() override = default;

	static constexpr qrpc::ServiceTag EchoTag = 1;
	static constexpr qrpc::ServiceTag EchoRequestTag = EchoRequest::tag;
	static constexpr qrpc::ServiceTag EchoResponseTag = EchoResponse::tag;
	void echo(EchoRequest *request, EchoResponse *response);

	static constexpr qrpc::ServiceTag EchoSampleTag = 2;
	static constexpr qrpc::ServiceTag EchoResponseSampleTag = EchoResponseSample::tag;
	static constexpr qrpc::ServiceTag EchoRequestSampleTag = EchoRequestSample::tag;
	void echoSample(EchoRequestSample *request, EchoResponseSample *response);
};

class Stub {
public:
	Stub(std::unique_ptr<qrpc::Connection> &&connection);

	static constexpr qrpc::ServiceTag EchoTag = 1;
	void echo(EchoRequest *request, EchoResponse *response);

	static constexpr qrpc::ServiceTag EchoSampleTag = 2;
	void echoSample(EchoRequestSample *request, EchoResponseSample *response);

private:
	std::unique_ptr<qrpc::Connection> m_connection;
	std::unique_ptr<qrpc::Call> m_callMethod;
};

#endif //QRPC_SERVICE_H
