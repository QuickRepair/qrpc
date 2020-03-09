#include "EpollReactorImplementation.h"
#include "EpollEvents.h"
#include "Server/Reactor/EventHandler.h"
#include <exception>
#include <cstring>
extern "C" {
#include <sys/epoll.h>
#include <sys/socket.h>
}

using std::make_unique;

namespace qrpc {
Reactor::Reactor()
{
	m_reactorImpl = make_unique<EpollReactorImplementation>();
}

EpollReactorImplementation::EpollReactorImplementation() : eventNums{0}
{
	if ((epfd = epoll_create(512)) == -1)
		throw std::runtime_error("Faile create epoll: " + std::string(strerror(errno)));
}

void EpollReactorImplementation::registerHandler(
		std::unique_ptr<EventHandler> &&eh, EventType et)
{
	Handle fd = eh->getHandle();
	HandleProperty handleProperty(fd, et);
	if (m_handles.find(handleProperty) == m_handles.end())
	{
		m_handles[handleProperty] = std::move(eh);
		epoll_event event;
		event.data.fd = fd;
		event.events = et;
		if (epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event) != 0/* && errno == EEXIST*/)
			throw std::runtime_error("Failed to register handle: " + std::string(strerror(errno)));
		++eventNums;
		events.resize(eventNums);
	}
}

void EpollReactorImplementation::updateHandler(EventHandler *eh,
											   EventType et)
{
	Handle fd = eh->getHandle();
	auto propertyIt = m_handles.find(HandleProperty(fd));
	if (propertyIt != m_handles.end())
	{
		EventType originalTypes = propertyIt->first.types;
		if (et & READ_EVENT)
			originalTypes = (originalTypes & READ_EVENT) ? (originalTypes & ~READ_EVENT) : (originalTypes | READ_EVENT);
		else if (et & WRITE_EVENT)
			originalTypes = (originalTypes & WRITE_EVENT) ? (originalTypes & ~WRITE_EVENT) : (originalTypes | WRITE_EVENT);
		else if (et & ERR_EVENT)
			originalTypes = (originalTypes & ERR_EVENT) ? (originalTypes & ~ERR_EVENT) : (originalTypes | ERR_EVENT);
		propertyIt->first.types = originalTypes;
		epoll_event event;
		event.data.fd = fd;
		event.events = originalTypes;
		if (epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &event) != 0/* && errno == ENOENT*/)
			throw std::runtime_error("Failed to update handle: " + std::string(strerror(errno)));
	}
}

// TODO remove one of the event type
/*void EpollReactorImplementation::removeHandler(EventHandler *eh, EventType et)
{
	Handle fd = eh->getHandle();
	if (m_handles.find(fd) == m_handles.end())
	{
		m_handles.erase(fd);
		if (epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL) != 0)
			throw std::runtime_error("Failed to remove handle");
		--eventNums;
		events.resize(eventNums);
	}
}*/

void EpollReactorImplementation::removeHandler(EventHandler *eh)
{
	Handle fd = eh->getHandle();
	HandleProperty handleProperty(fd);
	if (m_handles.find(handleProperty) == m_handles.end())
	{
		m_handles.erase(handleProperty);
		if (epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL) != 0)
			throw std::runtime_error("Failed to remove handle: " + std::string(strerror(errno)));
		--eventNums;
		events.resize(eventNums);
	}
}

void EpollReactorImplementation::handleEvents()
{
	int nums = epoll_wait(epfd, &events[0], eventNums, -1);
	for (int index = 0; index < nums; ++index)
	{
		uint32_t event = events[index].events;
		Handle fd = events[index].data.fd;
		HandleProperty handleProperty(fd);
		if (event & EPOLLIN)
			m_handles[handleProperty]->handleEvent(READ_EVENT);
		else if (event & EPOLLOUT)
			m_handles[handleProperty]->handleEvent(WRITE_EVENT);
		else if (event & EPOLLERR)
			m_handles[handleProperty]->handleEvent(ERR_EVENT);
	}
}
}