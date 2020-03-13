//
// Created by gaojian on 2019/12/23.
//

#ifndef REACTOR_SERVER_H
#define REACTOR_SERVER_H

#include <memory>

namespace qrpc {

class EventHandler;
class Service;
class MsgRepository;

class Server {
public:
	Server(std::string ip, unsigned port);
	void registerService(std::unique_ptr<Service> &&service);
	void registerMsgRepository(std::unique_ptr<MsgRepository> &&repository);
	void waitAndHandleMsg();

private:
	EventHandler *listener;
};
}

#endif //REACTOR_SERVER_H
