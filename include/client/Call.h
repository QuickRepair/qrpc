//
// Created by gaojian on 2020/1/2.
//

#ifndef QRPC_CALL_H
#define QRPC_CALL_H

#include <memory>
#include "net/ByteBuf.h"
#include "net/ReaderWriter.h"

namespace qrpc {

class Connection;
class Msg;

class Call {
public:
	explicit Call(Connection *connection) : _connection{connection} {}
	virtual ~Call() = default;
	virtual void call(qrpc::ServiceTag tag, Msg *request, Msg *response) = 0;

protected:
	Connection *_connection;
};

class BlockingCall : public Call {
public:
	explicit BlockingCall(Connection *connection);
	void call(qrpc::ServiceTag tag, Msg *request, Msg *response) override;

private:
	std::unique_ptr<RequestReader> reader;
	std::unique_ptr<ResponseWriter> writer;
};
}

#endif //QRPC_CALL_H
