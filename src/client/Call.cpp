//
// Created by gaojian on 2020/1/2.
//

#include "code_gen/MsgPackage.h"
#include "code_gen/SDStream.h"
#include "client/Call.h"
#include "client/Connection.h"
#include "code_gen/Msg.h"
#include "impl/ReaderWriterImplement.h"

using std::make_unique;

namespace qrpc {
BlockingCall::BlockingCall(Connection *connection)
	: Call(connection), reader{make_unique<LinuxReaderImplement>()}, writer{make_unique<LinuxWriterImplement>()}
{}

void BlockingCall::call(qrpc::ServiceTag tag, qrpc::Msg *request, qrpc::Msg *response)
{
	std::unique_ptr<ByteBuf> recvBuf;
	// send
	SerializeStream ss = MsgPackage::build(tag, request);
	Handle handle = _connection->getHandle();
	writer->send(handle, ss.get().get());

	// recv
	DeserializeStream ds(std::move(reader->recv(handle)));
	MsgPackage::getResponse(ds, response);
}
}
