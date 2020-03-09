//
// Created by gaojian on 2019/12/27.
//

#include "MsgGen.h"
#include "impl/ByteBuf.h"

size_t EchoRequest::byteSize() const
{
	return sizeof(m_msg);
}

void EchoRequest::serialize(qrpc::ServiceSerialize *serializing)
{
	serializing->writeChar(m_msg);
}

void EchoRequest::deserialize(const char *buf)
{
	m_msg = buf[0];
}

size_t EchoResponse::byteSize() const
{
	return sizeof(m_msg);
}

void EchoResponse::serialize(qrpc::ServiceSerialize *serializing)
{
	serializing->writeChar(getMsg());
}

void EchoResponse::deserialize(const char *buf)
{
	m_msg = buf[0];
}

size_t EchoRequestSample::byteSize() const
{
	return sizeof(m_msg);
}

void EchoRequestSample::serialize(qrpc::ServiceSerialize *serializing)
{
	serializing->writeChar(m_msg);
}

void EchoRequestSample::deserialize(const char *buf)
{
	m_msg = buf[0];
}

size_t EchoResponseSample::byteSize() const
{
	return sizeof(m_msg);
}

void EchoResponseSample::serialize(qrpc::ServiceSerialize *serializing)
{
	serializing->writeChar(getMsg());
}

void EchoResponseSample::deserialize(const char *buf)
{
	m_msg = buf[0];
}