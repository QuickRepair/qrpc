//
// Created by gaojian on 2020/3/25.
//

#ifndef QGEN_ARGPARSE_H
#define QGEN_ARGPARSE_H

#include <string>

namespace qrpc::CodeGen {
class ArgParse {
public:
	ArgParse(int argc, char *argv[]);

	std::string inputFileName();

private:
	int argNum;
	char **args;
};
}

#endif //QGEN_ARGPARSE_H
