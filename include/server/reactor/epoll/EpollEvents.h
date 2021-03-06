#ifndef QRPC_REACTOR_EPOLL_EVENTS_H
#define QRPC_REACTOR_EPOLL_EVENTS_H

extern "C" {
#include <sys/epoll.h>
}

namespace qrpc {
/// @brief epoll events type
enum:unsigned {
	WRITE_EVENT = EPOLLOUT,
	READ_EVENT = EPOLLIN,
	ERR_EVENT = EPOLLERR,
	DISCONNECT_EVENT = EPOLLRDHUP,
};
}

#endif