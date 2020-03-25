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

void CPPCodeGen::renderMessageClassPropertyHeader(const std::string &type, const std::string &attrName)
{
	message_gen_hpp_setter_and_getter.emplace_back(CPP::setterAndGetterDecl(type, attrName));
	message_gen_hpp_attr.emplace_back(CPP::messageClassProperty(type, attrName));
}

void CPPCodeGen::doneMessageClassHeaderRender(const std::string &className)
{
	std::string setterGetterDecl;
	for (auto &s : message_gen_hpp_setter_and_getter)
		setterGetterDecl += s;
	message_gen_hpp_setter_and_getter.clear();
	std::string classProperty;
	for (auto &s : message_gen_hpp_attr)
		classProperty += s;
	message_gen_hpp_attr.clear();
	std::string tag = std::to_string(message_gen_hpp_class_def.size());
	message_gen_hpp_class_def.emplace_back(CPP::messageClassDef(className, tag, setterGetterDecl, classProperty));
}

void CPPCodeGen::renderMessageClassPropertySource(const std::string &serializeClassName, const std::string &attrName)
{
	message_gen_byte_size_def.emplace_back(CPP::messageByteSizeDef(serializeClassName, attrName));
	message_gen_serialized_byte_size_def.emplace_back(CPP::messageSerializedByteSizeDef(serializeClassName, attrName));
	message_gen_serialize_def.emplace_back(CPP::messageSerializeDef(serializeClassName, attrName));
	message_gen_deserialize_def.emplace_back(CPP::messageDeserializeDef(serializeClassName, attrName));
}

void CPPCodeGen::doneMessageClassSourceRender(const std::string &className)
{
	std::string byteSizeDef;
	for (auto &s : message_gen_byte_size_def)
		byteSizeDef += s;
	message_gen_byte_size_def.clear();
	std::string serializedByteSizeDef;
	for (auto &s : message_gen_serialized_byte_size_def)
		serializedByteSizeDef += s;
	message_gen_serialized_byte_size_def.clear();
	std::string serializeDef;
	for (auto &s : message_gen_serialize_def)
		serializeDef += s;
	message_gen_serialize_def.clear();
	std::string deserializeDef;
	for (auto &s : message_gen_deserialize_def)
		deserializeDef += s;
	message_gen_deserialize_def.clear();
	message_gen_method_def.emplace_back(CPP::messageMethodDef(className, byteSizeDef, serializedByteSizeDef, serializeDef, deserializeDef));
}

std::string CPPCodeGen::getServiceHeader(const std::string &messageHeaderFileName)
{
	std::string forwardDecl;
	for (auto &s : service_gen_h_forward_decl)
		forwardDecl += s;
	std::string serviceRpcDecl;
	for (auto &s : service_gen_h_service_rpc_method_decl)
		serviceRpcDecl += s;
	std::string clientRpcDecl;
	for (auto &s : service_gen_h_client_rpc_method_decl)
		clientRpcDecl += s;
	std::string include = CPP::includeHeader(messageHeaderFileName);
	return CPP::serviceHpp(include, forwardDecl, serviceRpcDecl, clientRpcDecl);
}

std::string CPPCodeGen::getServiceSource(const std::string &serviceHeaderFileName)
{
	std::string registerMethods;
	for (auto &s : service_gen_cpp_register_services_method)
		registerMethods += s;
	std::string stubMethods;
	for (auto &s : service_gen_cpp_stub_method)
		stubMethods += s;
	std::string include = CPP::includeHeader(serviceHeaderFileName);
	return CPP::serviceCpp(include, registerMethods, stubMethods);
}

std::string CPPCodeGen::getMessageHeader()
{
	std::string classes;
	for (auto &s : message_gen_hpp_class_def)
		classes += s;
	return CPP::messageHpp(classes);
}

std::string CPPCodeGen::getMessageSource(const std::string &messageHeaderFileName)
{
	std::string methods;
	for (auto &s : message_gen_method_def)
		methods += s;
	std::string include = CPP::includeHeader(messageHeaderFileName);
	return CPP::messageCpp(include, methods);
}
}
