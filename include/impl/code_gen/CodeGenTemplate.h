//
// Created by gaojian on 2020/3/24.
//

#ifndef QGEN_CODEGENTEMPLATE_H
#define QGEN_CODEGENTEMPLATE_H

#include "template/CppServiceOut.h"
#include "template/CppMessageOut.h"
#include <vector>

namespace qrpc::CodeGen::CodeTemplate {
class CodeGenTemplate {
public:

};

class CPPCodeGen : CodeGenTemplate {
public:
	void renderServiceHeader(const std::string &serviceName, const std::string &request, const std::string &response);
	void renderServiceSource(const std::string &serviceName, const std::string &request, const std::string &response);
	void renderMessageClassPropertyHeader(const std::string &type, const std::string &attrName);
	void doneMessageClassHeaderRender(const std::string &className);
	void renderMessageClassPropertySource(const std::string &serializeClassName, const std::string &attrName);
	void doneMessageClassSourceRender(const std::string &className);
	std::string getServiceHeader(const std::string &messageHeaderFileName);
	std::string getServiceSource(const std::string &serviceHeaderFileName);
	std::string getMessageHeader();
	std::string getMessageSource(const std::string &messageHeaderFileName);
private:
	// service *.h
	std::vector<std::string> service_gen_h_forward_decl;
	std::vector<std::string> service_gen_h_service_rpc_method_decl;
	std::vector<std::string> service_gen_h_client_rpc_method_decl;
	// service *.cpp
	std::vector<std::string> service_gen_cpp_register_services_method;
	std::vector<std::string> service_gen_cpp_stub_method;
	// message *.h
	std::vector<std::string> message_gen_hpp_setter_and_getter;
	std::vector<std::string> message_gen_hpp_attr;
	std::vector<std::string> message_gen_hpp_class_def;
	// message *.cpp
	std::vector<std::string> message_gen_byte_size_def;
	std::vector<std::string> message_gen_serialized_byte_size_def;
	std::vector<std::string> message_gen_serialize_def;
	std::vector<std::string> message_gen_deserialize_def;
	std::vector<std::string> message_gen_method_def;
};
}

#endif //QGEN_CODEGENTEMPLATE_H
