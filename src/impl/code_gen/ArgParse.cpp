//
// Created by gaojian on 2020/3/25.
//

#include "impl/code_gen/ArgParse.h"

namespace qrpc::CodeGen {
ArgParse::ArgParse(int argc, char *argv[])
	: argNum{argc}, args{argv}
{}

std::string ArgParse::inputFileName()
{
	if (argNum > 1)
		return args[1];
	else
		return "";
}
}