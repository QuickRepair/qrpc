//
// Created by gaojian on 2020/3/25.
//

#include "impl/code_gen/template/CppMessageOut.h"

namespace qrpc::CodeGen::CodeTemplate::CPP {
std::string setterAndGetterDecl(const std::string &type, const std::string &attr)
{
	std::string output = message_gen_hpp_setter_and_getter;
	replace(output, "{%attr_name}", attr);
	replace(output, "{%type}", type);
	return output;
}

std::string messageClassProperty(const std::string &type, const std::string &attr)
{
	std::string output = message_gen_hpp_attr;
	replace(output, "{%attr_name}", attr);
	replace(output, "{%type}", type);
	return output;
}

std::string messageClassDef(const std::string &className, const std::string &tag, const std::string &setterGetter, const std::string &property)
{
	std::string output = message_gen_hpp_class_def;
	replace(output, "{%message_name}", className);
	replace(output, "{%tag}", tag);
	replace(output, "{%message_gen_hpp_setter_and_getter}", setterGetter);
	replace(output, "{%message_gen_hpp_attr}", property);
	return output;
}

std::string messageByteSizeDef(const std::string &serializeClass, const std::string &attr)
{
	std::string output = message_gen_cpp_byte_size_def;
	replace(output, "{%serialize_class}", serializeClass);
	replace(output, "{%attr_name}", attr);
	return output;
}

std::string messageSerializedByteSizeDef(const std::string &serializeClass, const std::string &attr)
{
	std::string output = message_gen_cpp_serialize_byte_size_def;
	replace(output, "{%serialize_class}", serializeClass);
	replace(output, "{%attr_name}", attr);
	return output;
}

std::string messageSerializeDef(const std::string &serializeClass, const std::string &attr)
{
	std::string output = message_gen_cpp_serialize_def;
	replace(output, "{%serialize_class}", serializeClass);
	replace(output, "{%attr_name}", attr);
	return output;
}

std::string messageDeserializeDef(const std::string &serializeClass, const std::string &attr)
{
	std::string output = message_gen_cpp_deserialzie_def;
	replace(output, "{%serialize_class}", serializeClass);
	replace(output, "{%attr_name}", attr);
	return output;
}

std::string messageMethodDef(const std::string &messageClass, const std::string &byteSizeMethodDef,
							 const std::string &serializedByteSizeMethodDef, const std::string &serializeMethodDef,
							 const std::string &deserializeMethodDef)
{
	std::string output = message_gen_method_def;
	replace(output, "{%message_name}", messageClass);
	replace(output, "{%message_gen_cpp_byte_size_def}", byteSizeMethodDef);
	replace(output, "{%message_gen_cpp_serialize_byte_size_def}", serializedByteSizeMethodDef);
	replace(output, "{%message_gen_cpp_serialize_def}", serializeMethodDef);
	replace(output, "{%message_gen_cpp_deserialzie_def}", deserializeMethodDef);
	return output;
}

std::string messageHpp(const std::string &classes)
{
	std::string output = message_gen_hpp;
	replace(output, "{%message_gen_hpp_class_def}", classes);
	return output;
}

std::string messageCpp(const std::string &include, const std::string &methods)
{
	std::string output = message_gen_cpp;
	replace(output, "{%message_gen_cpp_include_message_h}", include);
	replace(output, "{%message_gen_method_def}", methods);
	return output;
}
}
