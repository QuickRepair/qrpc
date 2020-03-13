#ifndef QRPC_EPOLL_REACTOR_IMPLEMENTATION_H
#define QRPC_EPOLL_REACTOR_IMPLEMENTATION_H

#include "include/impl/Handle.h"
#include "include/server/reactor/Reactor.hpp"
#include <map>
#include <vector>
extern "C" {
#include <sys/epoll.h>
}

namespace qrpc {
/// @brief Reactor implement with epoll
class EpollReactorImplementation : public ReactorImplementation {
public:
	EpollReactorImplementation();
	~EpollReactorImplementation() override = default;

	void registerHandler(std::unique_ptr<EventHandler> &&eh,
						 EventType et) override;
	void updateHandler(EventHandler *eh, EventType et) override;
	void removeHandler(EventHandler *eh) override;
	void handleEvents() override;

private:
	int epfd;
	unsigned eventNums;
	std::vector<epoll_event> events;

	struct HandleProperty {
		explicit HandleProperty(Handle &h) : handle{h}, types{0} {}
		HandleProperty(Handle &h, EventType &et) : handle{h}, types{et} {}

		Handle handle;
		mutable EventType types;
	};

	struct HandlePropertyMapCmp {
		bool operator()(const HandleProperty &l, const HandleProperty &r) const
		{
			return l.handle > r.handle;
		}
	};

	std::map<HandleProperty, std::unique_ptr<EventHandler>, HandlePropertyMapCmp> m_handles;
};
}

#endif
