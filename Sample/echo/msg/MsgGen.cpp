//
// Created by gaojian on 2019/12/27.
//

#include "MsgGen.h"
#include "impl/ByteBuf.h"

size_t EchoCharRequest::byteSize() const
{
	return sizeof(m_msg);
}

void EchoCharRequest::serialize(qrpc::ServiceSerialize *serializing)
{
	serializing->writeChar(m_msg);
}

void EchoCharRequest::deserialize(const char *buf)
{
	m_msg = buf[0];
}

size_t EchoCharResponse::byteSize() const
{
	return sizeof(m_msg);
}

void EchoCharResponse::serialize(qrpc::ServiceSerialize *serializing)
{
	serializing->writeChar(getMsg());
}

void EchoCharResponse::deserialize(const char *buf)
{
	m_msg = buf[0];
}

size_t EchoRequestSample::byteSize() const
{
	return m_msg.length() + 1;
}

void EchoRequestSample::serialize(qrpc::ServiceSerialize *serializing)
{
	serializing->writeString(m_msg);
}

void EchoRequestSample::deserialize(const char *buf)
{
	m_msg.append(buf);
}

size_t EchoResponseSample::byteSize() const
{
	return m_msg.length() + 1;
}

void EchoResponseSample::serialize(qrpc::ServiceSerialize *serializing)
{
	serializing->writeString(getMsg());
}

void EchoResponseSample::deserialize(const char *buf)
{
	m_msg.append(buf);
}