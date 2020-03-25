#ifndef QRPC_SERVICE_OUT_HPP
#define QRPC_SERVICE_OUT_HPP

#include <string>

namespace qrpc::CodeGen::CodeTemplate::CPP {

/// @brief: common
const std::string include_header =
		R"(#include "{%include_header}")";
void replace(std::string &output, const std::string &&templateName, const std::string &replaceWith);
std::string includeHeader(const std::string &header);

/// @brief: gen service *.h template
const std::string service_gen_hpp_forward_decl = R"(
class {%message_class_name};)";
const std::string service_gen_hpp_server_rpc_method_decl = R"(
	static constexpr qrpc::ServiceTag {%service_name}Tag = {%tag};
	virtual void {%service_name}({%request_name} *request, {%response_name} *response) = 0;)";
const std::string service_gen_hpp_client_rpc_method_decl = R"(
	static constexpr qrpc::ServiceTag {%service_name}Tag = {%tag};
	void {%service_name}({%request_name} *request, {%response_name} *response);)";
const std::string service_gen_hpp = R"(
#ifndef QRPC_CODE_GEN_SERVICE_H
#define QRPC_CODE_GEN_SERVICE_H

#include "impl/Service.h"
#include "client/Call.h"
#include "client/Connection.h"
{%service_gen_hpp_include_message_gen}
{%service_gen_hpp_forward_decl}

class Service : public qrpc::Service {
public:
	Service();
	~Service() override = default;
	{%service_gen_hpp_server_rpc_method_decl}
};

class Stub {
public:
	Stub(std::unique_ptr<qrpc::Connection> &&connection);
	{%service_gen_hpp_client_rpc_method_decl}

private:
	std::unique_ptr<qrpc::Connection> m_connection;
	std::unique_ptr<qrpc::Call> m_callMethod;
};

#endif
)";

/// @brief: gen service *.cpp template
const std::string service_gen_cpp_register_services_method = R"(
	registerService(
		std::move(make_unique<qrpc::RpcMethodHandler<Service, {%request_name}, {%response_name}>>(std::mem_fn(&Service::{%service_name}), this)),
		{%service_name}Tag
	);)";
const std::string service_gen_cpp_stub_method = R"(
void Stub::{%service_name}({%request_name} *request, {%response_name} *response)
{
	m_callMethod->call({%service_name}Tag, request, response);
}
)";
const std::string service_gen_cpp = R"(
{%service_gen_cpp_include_service_h}
#include "impl/MethodWrapper.h"
#include "client/Call.h"
#include <memory>

using std::make_unique;

Service::Service()
{
	{%service_gen_cpp_register_services_method}
}

Stub::Stub(std::unique_ptr<qrpc::Connection> &&connection)
		: m_connection{std::move(connection)}, m_callMethod{make_unique<qrpc::BlockingCall>(m_connection.get())}
{}
{%service_gen_cpp_stub_method})";

std::string messageForwardDecl(const std::string &messageName);
std::string serverRpcMethodDecl(const std::string &service, const std::string &request, const std::string &response, const std::string &tag);
std::string clientRpcMethodDecl(const std::string &service, const std::string &request, const std::string &response, const std::string &tag);
std::string registerServiceMethodDef(const std::string &service, const std::string &request, const std::string &response);
std::string stubMethodDef(const std::string &service, const std::string &request, const std::string &response);

std::string serviceHpp(const std::string &include, const std::string &forwardDecl, const std::string &serviceRpc, const std::string &clientRpc);
std::string serviceCpp(const std::string &include, const std::string &registerMethods, const std::string &stubMethods);
}

#endif