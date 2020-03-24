//
// Created by gaojian on 2019/12/28.
//

#include <cstring>
#include "impl/MsgPackage.h"
#include "net/ByteBuf.h"
#include "impl/Service.h"
#include "impl/MethodWrapper.h"
#include "net/ReaderWriter.h"
#include "impl/Msg.h"
#include "impl/SDStream.h"

using std::make_unique;				using std::optional;
using std::nullopt;

namespace qrpc {
ByteBuf::ByteBuf(size_t bufSize)
	: size{bufSize}, msg_buff{new char[size]}
{
	memset(msg_buff, 0, bufSize);
}

ByteBuf::ByteBuf(ByteBuf &&buf) noexcept
	: msg_buff{buf.msg_buff}, size{buf.size}
{
	buf.msg_buff = nullptr;
}

//ByteBuf::ByteBuf(const ByteBuf &&buf) noexcept
//	: msg_buff{buf.msg_buff}, size{buf.size}
//{
//	buf.msg_buff = nullptr;
//}

ByteBuf::~ByteBuf()
{
	delete [] msg_buff;
}

/*std::unique_ptr<ByteBuf> ServiceSerialize::serialize(ServiceTag serviceTag, Msg *msg)
{
	size_t buf_size = msg->serializedByteSize() + sizeof(serviceTag) + sizeof(ByteBuf::size);

	PackMsg package(serviceTag, msg);
	SerializeStream ss(package.length());
	ss.putHeader(package);
	msg->serialize(ss);

	return std::move(buf);
}*/

/*std::unique_ptr<ByteBuf> ServiceSerialize::allocaMem(size_t size)
{
	auto byteBuf = make_unique<ByteBuf>(size);
	_buf = byteBuf.get();
	m_cursor = 0;
	m_size = size;
	return std::move(byteBuf);
}*/

/*void ServiceSerialize::writeChar(const char data)
{
	_buf->msg_buff[m_cursor++] = data;
}

void ServiceSerialize::writeString(const std::string &str)
{
	for (auto &s : str)
		_buf->msg_buff[m_cursor++] = s;
}

void ServiceSerialize::writeInt32(const int data)
{
	_buf->msg_buff[m_cursor++] = static_cast<char>(data >> 24);

}*/

/*ByteBufDeserialize::ByteBufDeserialize(qrpc::MsgRepository *repository)
	: _repository{repository}
{}

std::optional<ByteBufDeserialize::ServiceOut> ByteBufDeserialize::deserializeRequest(const ByteBuf *recvBuf)
{
	ByteBufDeserialize::ServiceOut out;
	out.serviceTag = recvBuf->msg_buff[0];
	out.request = _repository->create(_repository->getRequestTag(out.serviceTag));
	out.request->deserialize(recvBuf->msg_buff + sizeof(ServiceTag));
	out.response = _repository->create(_repository->getResponseTag(out.serviceTag));
	return std::move(out);
}

void ByteBufDeserialize::deserializeResponse(const ByteBuf *recvBuf, Msg *response)
{
	response->deserialize(recvBuf->msg_buff + sizeof(ServiceTag));
}*/

HandleRequest::HandleRequest(Service *service, MsgRepository *repository)
	: _service{service}, _repository{repository}
{}

std::shared_ptr<ByteBuf> HandleRequest::process(std::shared_ptr<ByteBuf> buf)
{
	DeserializeStream ds(buf);
	optional<MsgPackage::Request> out = MsgPackage::getRequest(ds, _repository);
	if (!out.has_value())
		return nullptr;
	const MethodHandler *handler = _service->getHandler(out->serviceTag);
	handler->run(out->request.get(), out->response.get());
	SerializeStream ss = std::move(MsgPackage::build(out->serviceTag, out->response.get()));
	return ss.get();
}
}
