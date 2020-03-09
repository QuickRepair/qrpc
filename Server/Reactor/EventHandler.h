#ifndef QRPC_REACTOR_EVENT_HANDLER_H
#define QRPC_REACTOR_EVENT_HANDLER_H

#include "EventType.h"
#include "impl/Handle.h"

namespace qrpc {
/// @brief Interface of reactor event handler
class EventHandler {
public:
	virtual ~EventHandler() = default;

	virtual void handleEvent(EventType et) = 0;
	virtual Handle getHandle() const = 0;
};
}

#endif