//
// Created by gaojian on 2019/12/23.
//

#include "Server.h"
#include "Reactor/Reactor.hpp"
#include "Reactor/EpollImplement/Handlers/ListeningHandler.h"
#include "Reactor/EpollImplement/EpollEvents.h"

using std::make_unique;			using std::unique_ptr;

namespace qrpc {
Server::Server(std::string ip, unsigned port)
{
	auto listeningHandler = make_unique<ListeningHandler>(ip, port);
	listener = listeningHandler.get();
	Reactor::instance().registerHandler(std::move(listeningHandler), READ_EVENT);
}

void Server::registerService(std::unique_ptr<Service> &&service)
{
	dynamic_cast<ListeningHandler *>(listener)->registerService(std::move(service));
}

void Server::waitAndHandleMsg()
{
	Reactor::instance().handleEvents();
}

void Server::registerMsgRepository(std::unique_ptr<MsgRepository> &&repository)
{
	dynamic_cast<ListeningHandler *>(listener)->registerMsgRepository(std::move(repository));
}
}