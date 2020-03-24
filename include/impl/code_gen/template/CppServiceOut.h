#ifndef QRPC_SERVICE_OUT_HPP
#define QRPC_SERVICE_OUT_HPP

#include <string>

namespace qrpc::CodeGen::CodeTemplate::CPP {

/// @brief: gen service *.h template
const std::string service_gen_hpp_include_message_gen = R"(
#include "{%message_gen_file}"
)";
const std::string service_gen_hpp_forward_decl = R"(
class {%message_class_name};
)";
const std::string service_gen_hpp_server_rpc_method_decl = R"(
static constexpr qrpc::ServiceTag {%service_name}Tag = {%tag};
void {%service_name}({%request_name} *request, {%response_name} *response) = 0;
)";
const std::string service_gen_hpp_client_rpc_method_decl = R"(
static constexpr qrpc::ServiceTag {%service_name}Tag = {%tag};
void {%service_name}({%request_name} *request, {%response_name} *response);
)";
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
const std::string service_gen_cpp_include_service_h = R"(
#include "{%service_gen_file}"
)";
const std::string service_gen_cpp_register_services_method = R"(
registerService(
			std::move(make_unique<qrpc::RpcMethodHandler<Service, {%request_name}, {%response_name}>>(std::mem_fn(&Service::{%service_name}), this)),
			{%service_name}Tag
	);
)";
const std::string service_gen_cpp_stub_method = R"(
void Stub::{%service_name}({%request_name} *request, {%response_name} *response)
{
	m_callMethod->call({%service_name}Tag, request, response);
}
)";
const std::string service_gen_cpp = R"(
{%service_gen_cpp_include_service_h}
#include "MsgGen.h"
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

{%service_gen_cpp_stub_method}
)";


void replace(std::string &output, const std::string &&templateName, const std::string &replaceWith)
{
	std::string::size_type pos = 0;
	while((pos = output.find(templateName, pos)) != std::string::npos)
		output.replace(pos, replaceWith.size(), replaceWith);
}
std::string messageForwardDecl(const std::string &messageName)
{
	std::string output = service_gen_hpp_forward_decl;
	replace(output, "{%message_class_name}", messageName);
	return output;
}
std::string serverRpcMethodDecl(const std::string &service, const std::string &request, const std::string &response, const std::string &tag)
{
	std::string output = service_gen_hpp_server_rpc_method_decl;
	replace(output, "{%service_name}", service);
	replace(output, "{%tag}", tag);
	replace(output, "{%request_name}", request);
	replace(output, "{%response_name}", response);
	return output;
}
std::string clientRpcMethodDecl(const std::string &service, const std::string &request, const std::string &response, const std::string &tag)
{
	std::string output = service_gen_hpp_client_rpc_method_decl;
	replace(output, "{%service_name}", service);
	replace(output, "{%tag}", tag);
	replace(output, "{%request_name}", request);
	replace(output, "{%response_name}", response);
	return output;
}
std::string registerServiceMethodDef(const std::string &service, const std::string &request, const std::string &response)
{
	std::string output = service_gen_hpp_client_rpc_method_decl;
	replace(output, "{%service_name}", service);
	replace(output, "{%request_name}", request);
	replace(output, "{%response_name}", response);
	return output;
}
std::string stubMethodDef(const std::string &service, const std::string &request, const std::string &response)
{
	std::string output = service_gen_hpp_client_rpc_method_decl;
	replace(output, "{%service_name}", service);
	replace(output, "{%request_name}", request);
	replace(output, "{%response_name}", response);
	return output;
}
}

#endif