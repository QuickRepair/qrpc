//
// Created by gaojian on 2020/3/25.
//

#ifndef QGEN_STREAM_H
#define QGEN_STREAM_H

#include <istream>
#include <ostream>
#include <fstream>

namespace qrpc::CodeGen {

class InputStream {
public:
	InputStream(std::istream &is, std::string &name);
	virtual ~InputStream() = 0;

	std::istream &getStream();
	std::string getName();

private:
	std::istream &istream;
	std::string streamName;
};

class FileInput final : public InputStream {
public:
	explicit FileInput(std::string fileName);
	~FileInput() override;

private:
	std::ifstream fstream;
};

class OutputStream {
public:
	OutputStream(std::ostream &os, std::string name);
	virtual ~OutputStream() = 0;

	std::ostream &getStream();
	std::string getName();

private:
	std::ostream &ostream;
	std::string streamName;
};

class FileOutput final : public OutputStream {
public:
	explicit FileOutput(std::string fileName);
	~FileOutput() override;

private:
	std::ofstream fstream;
};
}

//qrpc::CodeGen::InputStream &operator>>(qrpc::CodeGen::InputStream &is, std::string str);
//qrpc::CodeGen::OutputStream &operator<<(qrpc::CodeGen::OutputStream &is, std::string str);

#endif //QGEN_STREAM_H
