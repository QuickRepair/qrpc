//
// Created by gaojian on 2020/3/20.
//

#ifndef QRPC_QRPCGRAMMAR_H
#define QRPC_QRPCGRAMMAR_H

#include <boost/spirit/home/x3.hpp>
#include "AST.hpp"

namespace qrpc::CodeGen::Rule {
	boost::spirit::x3::rule<class start, AST::ASTContext> start = "start";
//	boost::spirit::x3::rule<class var_name, std::string> var_name = "var_name";
	boost::spirit::x3::rule<class service, AST::ServiceAST> service = "service";
	boost::spirit::x3::rule<class message, AST::MessageAST> message = "message";
//	boost::spirit::x3::rule<class msg_attr_type, std::string> msg_attr_type = "msg_attr_type";
	boost::spirit::x3::rule<class msg_attr, AST::MessageAttrDefAST> msg_attr = "msg_attr";
//[([](auto &ctx){ std::cout << _attr(ctx) << std::endl; })];
	auto const start_def = *service >> *message;
	auto const var_name = (+boost::spirit::x3::alpha);
	auto const service_def =
			boost::spirit::x3::lit("rpc")
			>> '(' >> var_name >> ')'
			>> "request" >> '(' >> var_name >> ')'
			>> "response" >> '(' >> var_name >> ')';
	auto const message_def =
			boost::spirit::x3::lit("message")
			>> var_name
			>> '{' >> *msg_attr >> '}';
	auto const msg_attr_type =
			boost::spirit::x3::string("char")
			| boost::spirit::x3::string("string");
	auto const msg_attr_def =
			msg_attr_type
			>> var_name
			>> ";";

	BOOST_SPIRIT_DEFINE(start, service, message, msg_attr)
}

#endif //QRPC_QRPCGRAMMAR_H
