#include <iostream>
#include "server/reactor/epoll/handlers/SocketHandler.h"
#include "server/reactor/epoll/EpollEvents.h"
#include "server/reactor/Reactor.hpp"
extern "C" {
#include <sys/socket.h>
}

using std::make_unique;

namespace qrpc {
SocketHandler::SocketHandler(Handle handle, Service *service, MsgRepository *msgRepository)
	: m_handle{handle}, handleRequest(service, msgRepository),
	recvReader{make_unique<LinuxReaderImplement>()}, sendWriter{make_unique<LinuxWriterImplement>()}
{}

SocketHandler::~SocketHandler()
{
	shutdown(m_handle, SHUT_RDWR);
	/*Reactor::instance().subReactor()->removeHandler(this);*/
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
		case DISCONNECT_EVENT:
			disconnected();
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
	Reactor::instance().subReactor()->updateHandler(this, WRITE_EVENT);
}

void SocketHandler::recvMsg()
{
	recvBuf = std::move(recvReader->recv(m_handle));
	if (auto response = handleRequest.process(std::move(recvBuf)))
	{
		sendBuf = std::move(response);
		Reactor::instance().subReactor()->updateHandler(this, WRITE_EVENT);
	}
}

void SocketHandler::disconnected()
{
	std::cout << "disconnect" << std::endl;
	Reactor::instance().subReactor()->removeHandler(this);
}
}
