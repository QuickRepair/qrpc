#include "ListeningHandler.h"
#include "Server/Reactor/EpollImplement/EpollEvents.h"
#include "Server/Reactor/Reactor.hpp"
#include "SocketHandler.h"
#include <cstring>
#include <memory>
#include <stdexcept>
extern "C" {
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
}

using std::make_unique;
using std::runtime_error;
using std::unique_ptr;

namespace qrpc {
ListeningHandler::ListeningHandler(std::string addr, unsigned port)
	: ListeningHandler(addr, port, nullptr)
{}

ListeningHandler::ListeningHandler(std::string addr, unsigned port, std::unique_ptr<Service> &&service)
	: m_service{std::move(service)}
{
	if ((m_handle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
		throw runtime_error("socket: " + std::string(strerror(errno)));
	sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	if (addr == "0.0.0.0")
		server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	else
		server_addr.sin_addr.s_addr = inet_addr(addr.c_str());
	server_addr.sin_port = htons(port);
	if (bind(m_handle, (sockaddr *) &server_addr, sizeof(server_addr)) == -1)
		throw runtime_error("bind: " + std::string(strerror(errno)));
	if (listen(m_handle, 10) == -1)
		throw runtime_error("listen: " + std::string(strerror(errno)));
}

ListeningHandler::~ListeningHandler()
{
	shutdown(m_handle, SHUT_RDWR);
	Reactor::instance().removeHandler(this);
}

void ListeningHandler::handleEvent(EventType et)
{
	Handle newClient;
	unique_ptr<EventHandler> handler;
	switch (et)
	{
		case READ_EVENT:
			if ((newClient = accept(m_handle, NULL, NULL)) == -1)
				throw runtime_error("accept: " + std::string(strerror(errno)));
			handler = make_unique<SocketHandler>(newClient, m_service.get(), m_repository.get());
			Reactor::instance().registerHandler(std::move(handler), READ_EVENT);
			break;
		default:break;
	}
}

Handle ListeningHandler::getHandle() const
{
	return m_handle;
}

void ListeningHandler::registerService(std::unique_ptr<Service> &&service)
{
	m_service = std::move(service);
}

void ListeningHandler::registerMsgRepository(std::unique_ptr<MsgRepository> &&repository)
{
	m_repository = std::move(repository);
}
}