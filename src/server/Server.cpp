//
// Created by gaojian on 2019/12/23.
//

#include "server/Server.h"
#include "server/reactor/Reactor.hpp"
#include "server/reactor/epoll/handlers/ListeningHandler.h"
#include "server/reactor/epoll/EpollEvents.h"

using std::make_unique;			using std::unique_ptr;

namespace qrpc {
Server::Server(std::string ip, unsigned port)
{
	auto listeningHandler = make_unique<ListeningHandler>(ip, port);
	listener = listeningHandler.get();
	Reactor::instance().mainReactor()->registerHandler(std::move(listeningHandler), READ_EVENT);
}

void Server::registerService(std::unique_ptr<Service> &&service)
{
	dynamic_cast<ListeningHandler *>(listener)->registerService(std::move(service));
}

void Server::waitAndHandleMsg()
{
	Reactor::instance().run();
}

void Server::registerMsgRepository(std::unique_ptr<MsgRepository> &&repository)
{
	dynamic_cast<ListeningHandler *>(listener)->registerMsgRepository(std::move(repository));
}
}