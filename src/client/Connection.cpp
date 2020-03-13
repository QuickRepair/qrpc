//
// Created by gaojian on 2020/1/1.
//

#include "client/Connection.h"
#include <stdexcept>
#include <arpa/inet.h>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>

using std::runtime_error;

namespace qrpc {
Connection::Connection(std::string addr, unsigned port)
{
	if ((m_handle = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		throw runtime_error("socket error");
	::sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(addr.c_str());
	server_addr.sin_port = htons(port);
	if (connect(m_handle, (sockaddr *) &server_addr, sizeof(server_addr)) == -1)
		throw runtime_error("can not connect");
}

Connection::~Connection()
{
	shutdown(m_handle, SHUT_RDWR);
}

const Handle & Connection::getHandle() const
{
	return m_handle;
}
}