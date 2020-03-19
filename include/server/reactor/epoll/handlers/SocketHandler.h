#ifndef QRPC_REACTOR_SOCKET_HANDLER_H
#define QRPC_REACTOR_SOCKET_HANDLER_H

#include "include/server/reactor/EventHandler.h"
#include "include/impl/ReaderWriterImplement.h"
#include "include/impl/ByteBuf.h"
#include <future>

namespace qrpc {

class Service;
class MsgRepository;

/// @brief Handle a connection with client
class SocketHandler : public EventHandler {
public:
	SocketHandler(Handle handle, Service *service, MsgRepository *msgRepository);
	~SocketHandler() override;

	void handleEvent(EventType et) override;
	Handle getHandle() const override;

private:
	void sendMsg();
	void recvMsg();
	void disconnected();

	HandleRequest handleRequest;
	std::unique_ptr<RequestReader> recvReader;
//	std::shared_ptr<ByteBuf> recvBuf;
	std::unique_ptr<ResponseWriter> sendWriter;
//	std::shared_ptr<ByteBuf> sendBuf;
	std::future<std::shared_ptr<ByteBuf>> response;
	Handle m_handle;
};
}

#endif