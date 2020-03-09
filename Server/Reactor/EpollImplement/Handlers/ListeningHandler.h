#ifndef QRPC_REACTOR_LISTEN_HANDLER_H
#define QRPC_REACTOR_LISTEN_HANDLER_H

#include "Server/Reactor/EventHandler.h"
#include "CodeGen/Msg.h"
#include <string>
#include <memory>

namespace qrpc {

class Service;
class MsgRepository;

/// @brief: Accept connection handler
class ListeningHandler : public EventHandler {
public:
	ListeningHandler(std::string addr, unsigned port);
	ListeningHandler(std::string addr, unsigned port, std::unique_ptr<Service> &&service);
	~ListeningHandler() override;

	void handleEvent(EventType et) override;
	Handle getHandle() const override;

	void registerService(std::unique_ptr<Service> &&service);
	void registerMsgRepository(std::unique_ptr<MsgRepository> &&repository);

private:
	std::unique_ptr<Service> m_service;
	std::unique_ptr<MsgRepository> m_repository;
	Handle m_handle;
};
}

#endif