#include "SocketHandler.h"
#include "Server/Reactor/EpollImplement/EpollEvents.h"
#include "Server/Reactor/Reactor.hpp"
extern "C" {
#include <sys/socket.h>
}

using std::make_unique;

namespace qrpc {
SocketHandler::SocketHandler(Handle handle, Service *service, MsgRepository *msgRepository)
	: m_handle{handle}, handleRequest(service, msgRepository),
	recvReader{make_unique<LinuxReaderImplement>()}, sendWriter{make_unique<LinuxWriterImplement>()},
	recvBuf{make_unique<ByteBuf>()}, sendBuf{make_unique<ByteBuf>()}
{}

SocketHandler::~SocketHandler()
{
	shutdown(m_handle, SHUT_RDWR);
	Reactor::instance().removeHandler(this);
}

void SocketHandler::handleEvent(EventType et)
{
	switch (et)
	{
		case READ_EVENT:
			recvMsg();
			break;
		case WRITE_EVENT:
			sendMsg();
			break;
	}
}

Handle SocketHandler::getHandle() const
{
	return m_handle;
}

void SocketHandler::sendMsg()
{
	sendWriter->send(m_handle, sendBuf.get());
	Reactor::instance().updateHandler(this, WRITE_EVENT);
}

void SocketHandler::recvMsg()
{
	recvReader->recv(m_handle, recvBuf.get());
	if (auto response = handleRequest.process(recvBuf.get()))
	{
		sendBuf = std::move(response);
		Reactor::instance().updateHandler(this, WRITE_EVENT);
	}
}
}
