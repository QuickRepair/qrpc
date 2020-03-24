//
// Created by gaojian on 2020/3/22.
//

#ifndef QGEN_AST_HPP
#define QGEN_AST_HPP

#include <string>
#include <vector>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

namespace qrpc::CodeGen::AST {

struct ServiceAST;
struct MessageAST;
struct MessageAttrDefAST;

struct AST {};

struct ASTContext : public AST {
	std::vector<ServiceAST> services;
	std::vector<MessageAST> messages;
};

struct ServiceAST {
	std::string serviceName;
	std::string requestName;
	std::string responseName;
};

struct MessageAttrDefAST : public AST {
	std::string type;
	std::string attrName;
};

struct MessageAST : public AST {
	std::string messageName;
	std::vector<MessageAttrDefAST> def;
};

enum class Type {
	Service,
	Message,
	MessageAttr
};

using boost::fusion::operator<<;
}

BOOST_FUSION_ADAPT_STRUCT(
		qrpc::CodeGen::AST::ASTContext,
		services,
		messages
)
BOOST_FUSION_ADAPT_STRUCT(
		qrpc::CodeGen::AST::ServiceAST,
		serviceName,
		requestName,
		responseName
)
BOOST_FUSION_ADAPT_STRUCT(
		qrpc::CodeGen::AST::MessageAST,
		messageName,
		def
)
BOOST_FUSION_ADAPT_STRUCT(
		qrpc::CodeGen::AST::MessageAttrDefAST,
		type,
		attrName
)
#endif //QGEN_AST_HPP
