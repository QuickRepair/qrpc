//
// Created by gaojian on 2020/3/24.
//

#include "impl/code_gen/CodeGenTemplate.h"

namespace qrpc::CodeGen::CodeTemplate {
void CPPCodeGen::renderServiceHeader(const std::string &serviceName, const std::string &request, const std::string &response)
{
	service_gen_h_forward_decl.emplace_back(CPP::messageForwardDecl(request));
	service_gen_h_forward_decl.emplace_back(CPP::messageForwardDecl(response));
	std::string tag = std::to_string(service_gen_h_service_rpc_method_decl.size());
	service_gen_h_service_rpc_method_decl.emplace_back(CPP::serverRpcMethodDecl(serviceName, request, response, tag));
	service_gen_h_client_rpc_method_decl.emplace_back(CPP::clientRpcMethodDecl(serviceName, request, response, tag));
}

void CPPCodeGen::renderServiceSource(const std::string &serviceName, const std::string &request, const std::string &response)
{
	service_gen_cpp_register_services_method.emplace_back(CPP::registerServiceMethodDef(serviceName, request, response));
	service_gen_cpp_stub_method.emplace_back(CPP::stubMethodDef(serviceName, request, response));
}
}
