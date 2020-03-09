//
// Created by gaojian on 2019/12/28.
//

#include "ByteBuf.h"
#include "CodeGen/Service.h"
#include "CodeGen/MethodWrapper.h"
#include "ReaderWriter.h"
#include "CodeGen/Msg.h"

using std::make_unique;				using std::optional;
using std::nullopt;

namespace qrpc {
ByteBuf::ByteBuf(size_t bufSize)
	: size{bufSize}, msg_buff{new char[size]}
{}

ByteBuf::~ByteBuf()
{
	delete [] msg_buff;
}

std::unique_ptr<ByteBuf> ServiceSerialize::serialize(ServiceTag serviceTag, Msg *msg)
{
	auto buf = allocaMem(msg->byteSize() + 1);
	buf->msg_buff[m_cursor++] = serviceTag;
	msg->serialize(this);
	return std::move(buf);
}

std::unique_ptr<ByteBuf> ServiceSerialize::allocaMem(size_t size)
{
	// TODO: make size changeable
	auto byteBuf = make_unique<ByteBuf>(/*size + 1*/);
	_buf = byteBuf.get();
	m_cursor = 0;
	m_size = size;
	return std::move(byteBuf);
}

void ServiceSerialize::writeChar(const char data)
{
	_buf->msg_buff[m_cursor++] = data;
}

ByteBufDeserialize::ByteBufDeserialize(qrpc::MsgRepository *repository)
	: _repository{repository}
{}

std::optional<ByteBufDeserialize::ServiceOut> ByteBufDeserialize::deserializeRequest(const ByteBuf *recvBuf)
{
	ByteBufDeserialize::ServiceOut out;
	out.serviceTag = recvBuf->msg_buff[0];
	out.request = _repository->create(_repository->getRequestTag(out.serviceTag));
	out.request->deserialize(recvBuf->msg_buff + 1);
	out.response = _repository->create(_repository->getResponseTag(out.serviceTag));
	return std::move(out);
}

void ByteBufDeserialize::deserializeResponse(const ByteBuf *recvBuf, Msg *response)
{
	response->deserialize(recvBuf->msg_buff + 1);
}

HandleRequest::HandleRequest(Service *service, MsgRepository *repository)
	: _service{service}, convert(repository)
{}

std::unique_ptr<ByteBuf> HandleRequest::process(const ByteBuf *buf)
{
	optional<ByteBufDeserialize::ServiceOut> out = convert.deserializeRequest(buf);
	if (!out.has_value())
		return nullptr;
	const MethodHandler *handler = _service->getHandler(out->serviceTag);
	handler->run(out->request.get(), out->response.get());
	ServiceSerialize serviceSerialize;
	return std::move(serviceSerialize.serialize(out->serviceTag, out->response.get()));
}
}
