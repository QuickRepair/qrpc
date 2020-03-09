//
// Created by gaojian on 2019/12/28.
//

#ifndef QRPC_METHODWRAPPER_H
#define QRPC_METHODWRAPPER_H

#include <functional>
#include <memory>

namespace qrpc {

class Msg;

/// @brief: Interface of service method wrapper
class MethodHandler {
public:
	virtual ~MethodHandler() = 0;
	virtual void run(void *request, void *response) const = 0;
};

template<typename ServiceType, typename Request, typename Response>
class RpcMethodHandler : public MethodHandler {
public:
	RpcMethodHandler(std::function<void(ServiceType *, Request *, Response *)> func, ServiceType *service)
		: _service{service}, _handler{func}
	{}

	~RpcMethodHandler() override = default;
	void run(void *request, void *response) const override
	{
		_handler(_service, static_cast<Request *>(request), static_cast<Response *>(response));
	}

private:
	ServiceType *_service;
	std::function<void(ServiceType *, Request *, Response *)> _handler;
};

/// @brief: Interface of Msg creator method
class MessageCreator {
public:
	virtual ~MessageCreator() = 0;
	virtual std::unique_ptr<Msg> create() = 0;
};

template<typename MsgType>
class RpcMessageCreator : public MessageCreator {
public:
	explicit RpcMessageCreator(std::function<std::unique_ptr<MsgType>()> func)
		: m_creator{func}
	{}

	~RpcMessageCreator() override = default;

	std::unique_ptr<Msg> create() override
	{
		return std::move(m_creator());
	}

private:
	std::function<std::unique_ptr<MsgType>()> m_creator;
};
}


#endif //QRPC_METHODWRAPPER_H
