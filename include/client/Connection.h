//
// Created by gaojian on 2020/1/1.
//

#ifndef QRPC_CONNECTION_H
#define QRPC_CONNECTION_H

#include "net/Handle.h"
#include <string>

namespace qrpc {
class Connection {
public:
	Connection(std::string addr, unsigned port);
	~Connection();
	const Handle &getHandle() const;

private:
	Handle m_handle;
};
}

#endif //QRPC_CONNECTION_H
