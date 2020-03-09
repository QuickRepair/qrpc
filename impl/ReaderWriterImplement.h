//
// Created by gaojian on 2019/12/20.
//

#ifndef QRPC_REACTOR_READERWRITERIMPLEMENT_H
#define QRPC_REACTOR_READERWRITERIMPLEMENT_H

#include "ReaderWriter.h"

namespace qrpc {
class LinuxReaderImplement : public RequestReader {
public:
	~LinuxReaderImplement() override = default;
	void recv(Handle handle, ByteBuf *buf) override;
};

class LinuxWriterImplement : public ResponseWriter {
public:
	~LinuxWriterImplement() override = default;
	void send(Handle handle, const ByteBuf *buf) override;
};
}

#endif //REACTOR_READERWRITERIMPLEMENT_H
