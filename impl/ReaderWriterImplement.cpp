//
// Created by gaojian on 2019/12/20.
//

#include "ReaderWriterImplement.h"
#include "impl/ByteBuf.h"
#include <sys/socket.h>

using std::make_unique;

namespace qrpc {

void LinuxReaderImplement::recv(Handle handle, ByteBuf *buf)
{
	/*msghdr msg;
	iovec iov;

	iov.iov_base = buf->msg_buff;
	iov.iov_len = buf->DEFAULT_BUF_SIZE;

	msg.msg_name = NULL;
	msg.msg_namelen = 0;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_control = NULL;
	msg.msg_controllen = 0;
	msg.msg_flags = 0;
	recvmsg(handle, &msg, 0);*/
	size_t len;
	::recv(handle, &len, sizeof(ByteBuf::size), 0);
	size_t read = len - sizeof(ByteBuf::size);
	::recv(handle, buf->msg_buff, read, 0);
}

void LinuxWriterImplement::send(Handle handle, const ByteBuf *buf)
{
	/*msghdr msg;
	iovec iov;

	iov.iov_base = buf->msg_buff;
	iov.iov_len = buf->DEFAULT_BUF_SIZE;

	msg.msg_name = NULL;
	msg.msg_namelen = 0;
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_control = NULL;
	msg.msg_controllen = 0;
	msg.msg_flags = 0;
	sendmsg(handle, &msg, 0);*/
	::send(handle, buf->msg_buff, buf->size, 0);
}
}
