//
// Created by gaojian on 2019/12/27.
//

#include "MsgGen.h"
#include "net/ByteBuf.h"
#include "impl/Serializable.h"

size_t EchoCharRequest::byteSize()
{
	qrpc::CharSerialize msg(m_msg);
	return msg.byteSize();
}

size_t EchoCharRequest::serializedByteSize()
{
	qrpc::CharSerialize msg(m_msg);
	return msg.serializedByteSize();
}

void EchoCharRequest::serialize(qrpc::SerializeStream &stream)
{
	qrpc::CharSerialize msg(m_msg);
	msg.serialize(stream);
}

void EchoCharRequest::deserialize(qrpc::DeserializeStream &stream)
{
	qrpc::CharSerialize msg(m_msg);
	msg.deserialize(stream);
}

size_t EchoCharResponse::byteSize()
{
	qrpc::CharSerialize msg(m_msg);
	return msg.byteSize();
}

size_t EchoCharResponse::serializedByteSize()
{
	qrpc::CharSerialize msg(m_msg);
	return msg.serializedByteSize();
}

void EchoCharResponse::serialize(qrpc::SerializeStream &stream)
{
	qrpc::CharSerialize msg(m_msg);
	msg.serialize(stream);
}

void EchoCharResponse::deserialize(qrpc::DeserializeStream &stream)
{
	qrpc::CharSerialize msg(m_msg);
	msg.deserialize(stream);
}

size_t EchoRequestSample::byteSize()
{
	qrpc::StringSerialize msg(m_msg);
	return msg.byteSize();
}

size_t EchoRequestSample::serializedByteSize()
{
	qrpc::StringSerialize msg(m_msg);
	return msg.serializedByteSize();
}

void EchoRequestSample::serialize(qrpc::SerializeStream &stream)
{
	qrpc::StringSerialize msg(m_msg);
	msg.serialize(stream);
}

void EchoRequestSample::deserialize(qrpc::DeserializeStream &stream)
{
	qrpc::StringSerialize msg(m_msg);
	msg.deserialize(stream);
}

size_t EchoResponseSample::byteSize()
{
	qrpc::StringSerialize msg(m_msg);
	return msg.byteSize();
}

size_t EchoResponseSample::serializedByteSize()
{
	qrpc::StringSerialize msg(m_msg);
	return msg.serializedByteSize();
}

void EchoResponseSample::serialize(qrpc::SerializeStream &stream)
{
	qrpc::StringSerialize msg(m_msg);
	msg.serialize(stream);
}

void EchoResponseSample::deserialize(qrpc::DeserializeStream &stream)
{
	qrpc::StringSerialize msg(m_msg);
	msg.deserialize(stream);
}