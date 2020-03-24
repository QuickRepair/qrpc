//
// Created by gaojian on 2019/12/26.
//

#ifndef QRPC_IMPL_SERVICE_H
#define QRPC_IMPL_SERVICE_H

#include <memory>
#include <vector>
#include <functional>
#include "MethodWrapper.h"

namespace qrpc {

class MethodHandler;

using ServiceTag = unsigned;

/// @brief Interface of service
class Service {
public:
	Service();
	virtual ~Service() = 0;

	void registerService(std::unique_ptr<MethodHandler> &&handler, ServiceTag tag);
	const MethodHandler *getHandler(ServiceTag tag) const;

	/// @note For every rpc method, must define
	/// static constexpr qrpc::ServiceTag RpcMethodTag = %d
	/// void RpcMethod(MethodRequest *, MethodResponse *);

private:
	std::vector<std::unique_ptr<MethodHandler>> m_handlers;
};
}

#endif //QRPC_SERVICE_H
