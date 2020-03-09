//
// Created by gaojian on 2020/1/2.
//

#include "Call.h"
#include "Connection.h"
#include "CodeGen/Msg.h"
#include "impl/ReaderWriterImplement.h"
#include <iostream>
#include <cstring>

using std::make_unique;

namespace qrpc {
BlockingCall::BlockingCall(Connection *connection)
	: Call(connection), reader{make_unique<LinuxReaderImplement>()}, writer{make_unique<LinuxWriterImplement>()}
{}

void BlockingCall::call(qrpc::ServiceTag tag, qrpc::Msg *request, qrpc::Msg *response)
{
	std::unique_ptr<ByteBuf> recvBuf;
	std::unique_ptr<ByteBuf> sendBuf;
	// send
	ServiceSerialize sendServiceSerialize;
	Handle handle = _connection->getHandle();
	sendBuf = sendServiceSerialize.serialize(tag, request);
	writer->send(handle, sendBuf.get());

	// recv
	ServiceSerialize recvServiceSerialize;
	recvBuf = recvServiceSerialize.serialize(tag, response);
	reader->recv(handle, recvBuf.get());
	ByteBufDeserialize::deserializeResponse(recvBuf.get(), response);
}
}
