#ifndef QRPC_REACTOR_H
#define QRPC_REACTOR_H

#include "EventType.h"
#include <memory>

namespace qrpc {

class EventHandler;

/// @brief Reactor interface
class ReactorImplementation {
public:
	virtual ~ReactorImplementation() = default;

	virtual void registerHandler(std::unique_ptr<EventHandler> &&eh,
									 EventType et) = 0;
	virtual void updateHandler(EventHandler *eh, EventType et) = 0;
	virtual void removeHandler(EventHandler *eh) = 0;
	virtual void handleEvents() = 0;
};

/// @brief Reactor singleton
class Reactor {
public:
	// implements in subclass of ReactorImplementation
	Reactor();

	void registerHandler(std::unique_ptr<EventHandler> &&eh, EventType et)
	{
		m_reactorImpl->registerHandler(std::move(eh), et);
	}

	void updateHandler(EventHandler *eh, EventType et)
	{
		m_reactorImpl->updateHandler(eh, et);
	}

	void removeHandler(EventHandler *eh)
	{
		m_reactorImpl->removeHandler(eh);
	}

	void handleEvents()
	{
		m_reactorImpl->handleEvents();
	}

	static Reactor &instance()
	{
		static Reactor reactor;
		return reactor;
	}

private:
	std::unique_ptr<ReactorImplementation> m_reactorImpl;
};
}

#endif