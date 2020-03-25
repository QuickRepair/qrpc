//
// Created by gaojian on 2020/3/25.
//

#include "impl/code_gen/template/CppServiceOut.h"

namespace qrpc::CodeGen::CodeTemplate::CPP {
void replace(std::string &output, const std::string &&templateName, const std::string &replaceWith)
{
	std::string::size_type pos = 0;
	while ((pos = output.find(templateName, pos)) != std::string::npos)
		output.replace(pos, templateName.size(), replaceWith);
}

std::string includeHeader(const std::string &header)
{
	std::string output = include_header;
	replace(output, "{%include_header}", header);
	return output;
}

std::string messageForwardDecl(const std::string &messageName)
{
	std::string output = service_gen_hpp_forward_decl;
	replace(output, "{%message_class_name}", messageName);
	return output;
}

std::string serverRpcMethodDecl(const std::string &service, const std::string &request, const std::string &response,
								const std::string &tag)
{
	std::string output = service_gen_hpp_server_rpc_method_decl;
	replace(output, "{%service_name}", service);
	replace(output, "{%tag}", tag);
	replace(output, "{%request_name}", request);
	replace(output, "{%response_name}", response);
	return output;
}

std::string clientRpcMethodDecl(const std::string &service, const std::string &request, const std::string &response,
								const std::string &tag)
{
	std::string output = service_gen_hpp_client_rpc_method_decl;
	replace(output, "{%service_name}", service);
	replace(output, "{%tag}", tag);
	replace(output, "{%request_name}", request);
	replace(output, "{%response_name}", response);
	return output;
}

std::string
registerServiceMethodDef(const std::string &service, const std::string &request, const std::string &response)
{
	std::string output = service_gen_cpp_register_services_method;
	replace(output, "{%service_name}", service);
	replace(output, "{%request_name}", request);
	replace(output, "{%response_name}", response);
	return output;
}

std::string stubMethodDef(const std::string &service, const std::string &request, const std::string &response)
{
	std::string output = service_gen_cpp_stub_method;
	replace(output, "{%service_name}", service);
	replace(output, "{%request_name}", request);
	replace(output, "{%response_name}", response);
	return output;
}

std::string serviceHpp(const std::string &include, const std::string &forwardDecl, const std::string &serviceRpc,
					   const std::string &clientRpc)
{
	std::string output = service_gen_hpp;
	replace(output, "{%service_gen_hpp_include_message_gen}", include);
	replace(output, "{%service_gen_hpp_forward_decl}", forwardDecl);
	replace(output, "{%service_gen_hpp_server_rpc_method_decl}", serviceRpc);
	replace(output, "{%service_gen_hpp_client_rpc_method_decl}", clientRpc);
	return output;
}

std::string serviceCpp(const std::string &include, const std::string &registerMethods, const std::string &stubMethods)
{
	std::string output = service_gen_cpp;
	replace(output, "{%service_gen_cpp_include_service_h}", include);
	replace(output, "{%service_gen_cpp_register_services_method}", registerMethods);
	replace(output, "{%service_gen_cpp_stub_method}", stubMethods);
	return output;
}
}
