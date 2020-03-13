//
// Created by gaojian on 2019/12/27.
//

#ifndef SERVICE_H
#define SERVICE_H

#include "include/code_gen/Service.h"
#include "include/client/Call.h"
#include "include/client/Connection.h"
#include "MsgGen.h"

class EchoCharRequest;
class EchoCharResponse;

class Service : public qrpc::Service {
public:
	Service();
	~Service() override = default;

	static constexpr qrpc::ServiceTag EchoTag = 1;
	void echo(EchoCharRequest *request, EchoCharResponse *response);

	static constexpr qrpc::ServiceTag EchoSampleTag = 2;
	void echoSample(EchoRequestSample *request, EchoResponseSample *response);
};

class Stub {
public:
	Stub(std::unique_ptr<qrpc::Connection> &&connection);

	static constexpr qrpc::ServiceTag EchoTag = 1;
	void echo(EchoCharRequest *request, EchoCharResponse *response);

	static constexpr qrpc::ServiceTag EchoSampleTag = 2;
	void echoSample(EchoRequestSample *request, EchoResponseSample *response);

private:
	std::unique_ptr<qrpc::Connection> m_connection;
	std::unique_ptr<qrpc::Call> m_callMethod;
};

#endif //QRPC_SERVICE_H
