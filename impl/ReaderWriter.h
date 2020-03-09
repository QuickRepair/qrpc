//
// Created by gaojian on 2019/12/23.
//

#ifndef QRPC_REACTOR_READERWRITER_H
#define QRPC_REACTOR_READERWRITER_H

#include "impl/Handle.h"
#include <memory>

namespace qrpc {

class ByteBuf;

/// @brief Reader
class RequestReader {
public:
	virtual ~RequestReader() = default;

	virtual void recv(Handle handle, ByteBuf *buf) = 0;
};

/// @brief Writer
class ResponseWriter {
public:
	virtual ~ResponseWriter() = default;

	virtual void send(Handle handle, const ByteBuf * buf) = 0;
};
}

#endif //REACTOR_READERWRITER_H
