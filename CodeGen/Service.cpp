//
// Created by gaojian on 2019/12/26.
//

#include "Service.h"
#include "MethodWrapper.h"

namespace qrpc {
Service::Service()
{}

Service::~Service()
{}

void Service::registerService(std::unique_ptr<MethodHandler> &&handler, unsigned tag)
{
	if (m_handlers.size() < tag + 1)
		m_handlers.resize(tag + 1);
	m_handlers[tag] = std::move(handler);
}

const MethodHandler * Service::getHandler(unsigned int tag) const
{
	if (m_handlers.size() < tag)
		return nullptr;
	return m_handlers[tag].get();
}
}