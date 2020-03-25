//
// Created by gaojian on 2020/3/25.
//

#include "impl/code_gen/TypeMap.h"

namespace qrpc::CodeGen::QRPCType {
TypeMap::TypeMap()
{
	map["char"] = "char";
	map["string"] = "std::string";
}

std::string TypeMap::get(const std::string &qrpcType)
{
	return map[qrpcType];
}

SerializeTypeMap::SerializeTypeMap()
{
	map["char"] = "qrpc::CharSerialize";
	map["string"] = "qrpc::StringSerialize";
}

std::string SerializeTypeMap::get(const std::string &qrpcType)
{
	return map[qrpcType];
}
}