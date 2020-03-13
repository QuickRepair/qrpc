//
// Created by gaojian on 2020/3/13.
//

#include "code_gen/Serializable.h"
#include "code_gen/MsgPackage.h"
#include "code_gen/SDStream.h"
#include "code_gen/Msg.h"

namespace qrpc {
SerializeStream MsgPackage::build(ServiceTag serviceTag, Msg *msg)
{
	size_t packageLength = msg->serializedByteSize() + sizeof(serviceTag) + sizeof(ByteBuf::size);
	SerializeStream ss(packageLength);
	Header header(packageLength, serviceTag);
	ss << header;
	msg->serialize(ss);
	return std::move(ss);
}

std::optional<MsgPackage::Request> MsgPackage::getRequest(DeserializeStream &stream, MsgRepository *repository)
{
	MsgPackage::Request out;
	Header header;
	stream >> header;
	out.serviceTag = header.tag;
	out.request = repository->create(repository->getRequestTag(out.serviceTag));
	out.request->deserialize(stream);
	out.response = repository->create(repository->getResponseTag(out.serviceTag));
	return std::move(out);
}

void MsgPackage::getResponse(DeserializeStream &stream, Msg *response)
{
	Header header;
	stream >> header;
	response->deserialize(stream);
}

Header::Header(size_t packageLength, qrpc::ServiceTag serviceTag)
	: len{packageLength}, tag{serviceTag}
{}
}