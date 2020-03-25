//
// Created by gaojian on 2020/3/25.
//

#include "impl/code_gen/Stream.h"

using std::ifstream;
using std::ofstream;

namespace qrpc::CodeGen {
InputStream::InputStream(std::istream &is, std::string &name)
	: istream{is}, streamName{name}
{}

InputStream::~InputStream()
{}

std::istream &InputStream::getStream()
{
	return istream;
}

std::string InputStream::getName()
{
	return streamName;
}

FileInput::FileInput(std::string fileName)
	: fstream{fileName}, InputStream(fstream, fileName)
{}

FileInput::~FileInput()
{
	fstream.close();
}

OutputStream::OutputStream(std::ostream &os, std::string name)
	: ostream{os}, streamName{name}
{}

OutputStream::~OutputStream()
{}

std::ostream & OutputStream::getStream()
{
	return ostream;
}

std::string OutputStream::getName()
{
	return streamName;
}

FileOutput::FileOutput(std::string fileName)
	: fstream{fileName}, OutputStream(fstream, fileName)
{}

FileOutput::~FileOutput()
{
	fstream.close();
}

//qrpc::CodeGen::InputStream &operator>>(qrpc::CodeGen::InputStream &is, std::string str)
//{
//	is >> str;
//	return is;
//}
}

/*qrpc::CodeGen::OutputStream &operator<<(qrpc::CodeGen::OutputStream &os, std::string str)
{
	os << str;
	return os;
}*/
