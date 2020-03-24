//
// Created by gaojian on 2020/3/20.
//

//#include "impl/code_gen/QrpcGrammar.h"

#include <iostream>
#include "impl/code_gen/AST.hpp"
#include "impl/code_gen/Visitor.h"
#include "impl/code_gen/SymbolTable.hpp"
#include "impl/code_gen/QrpcGrammar.hpp"

using namespace boost::spirit::x3;
using namespace qrpc::CodeGen;
using std::make_unique;

int main()
{
	AST::ASTContext context;
	std::string start_def(
	"rpc(echoChar) request(echoCRequest) response(echoCResponse)"
	"rpc(echoStr) request(echoSRequest) response(echoSResponse)"
	"message echoCRequest { char varname; }"
	"message echoCResponse { char varname; }"
	"message echoSRequest { char varname; }"
	"message echoSResponse { char varname; }"
	);
	boost::spirit::x3::phrase_parse(
			start_def.begin(), start_def.end(),
			Rule::start,
			ascii::space, context
	);
	auto st = make_unique<ST::STRoot>();
	Visitor::ASTBuildVisitor builder(st.get());
	builder.visitContext(context);
	Visitor::PrintVisitor printer(std::cout);
	printer.visitContext(context);

	return 0;
}
