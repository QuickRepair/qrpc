//
// Created by gaojian on 2020/3/20.
//

//#include "impl/code_gen/QrpcGrammar.h"

#include <iostream>
#include "impl/code_gen/AST.hpp"
#include "impl/code_gen/Visitor.h"
#include "impl/code_gen/SymbolTable.hpp"
#include "impl/code_gen/QrpcGrammar.hpp"
#include "impl/code_gen/ArgParse.h"
#include "impl/code_gen/Stream.h"

using namespace boost::spirit::x3;
using namespace qrpc::CodeGen;
using std::make_unique;

int main(int argc, char *argv[])
{
	ArgParse args(argc, argv);
	FileInput ifstream(args.inputFileName());
	AST::ASTContext context;
	/*std::string start_def(
	"rpc(echoChar) request(echoCRequest) response(echoCResponse)"
	"rpc(echoStr) request(echoSRequest) response(echoSResponse)"
	"message echoCRequest { char varname; }"
	"message echoCResponse { char varname; }"
	"message echoSRequest { string varname; }"
	"message echoSResponse { string varname; }"
	);*/
	std::string fileContent(std::istream_iterator<char>(ifstream.getStream()), std::istream_iterator<char>());
	boost::spirit::x3::phrase_parse(
			fileContent.begin(), fileContent.end(),
			Rule::start,
			ascii::space, context
	);
	auto st = make_unique<ST::STRoot>();
	Visitor::ASTBuildVisitor builder(st.get());
	builder.visitContext(context);
	/*Visitor::PrintVisitor printer(std::cout);
	printer.visitContext(context);*/
	FileOutput serviceHeader(args.inputFileName() + "_service.h");
	FileOutput serviceSource(args.inputFileName() + "_service.cpp");
	FileOutput messageHeader(args.inputFileName() + "_message.h");
	FileOutput messageSource(args.inputFileName() + "_message.cpp");
	Visitor::CodeGenVisitor codeGen(serviceHeader, serviceSource, messageHeader, messageSource);
	codeGen.visitContext(context);

	return 0;
}
