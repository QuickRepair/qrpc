//
// Created by gaojian on 2020/3/25.
//

#ifndef QGEN_TYPEMAP_H
#define QGEN_TYPEMAP_H

#include <string>
#include <unordered_map>

namespace qrpc::CodeGen::QRPCType {
/// @brief: convert qrpc type to c++ type
class TypeMap {
public:
	TypeMap();

	std::string get(const std::string &qrpcType);

private:
	std::unordered_map<std::string, std::string> map;
};

/// @brief: get serialize class for qrpc type
class SerializeTypeMap {
public:
	SerializeTypeMap();

	std::string get(const std::string &qrpcType);

private:
	std::unordered_map<std::string, std::string> map;
};
}
#endif //QGEN_TYPEMAP_H
