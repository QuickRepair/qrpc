//
// Created by gaojian on 2020/3/13.
//

#ifndef QRPC_MSGPACKAGE_H
#define QRPC_MSGPACKAGE_H

#include "Service.h"

namespace qrpc {

class SerializeStream;
class DeserializeStream;
class MsgRepository;

/// @brief Pack message
class MsgPackage {
public:
	struct Request {
		ServiceTag serviceTag;
		std::unique_ptr<Msg> request;
		std::unique_ptr<Msg> response;
	};

	static SerializeStream build(ServiceTag serviceTag, Msg *msg);
	static std::optional<Request> getRequest(DeserializeStream &stream, MsgRepository *repository);
	static void getResponse(DeserializeStream &stream, Msg *response);
};

struct Header {
	Header() = default;
	Header(size_t packageLength, ServiceTag serviceTag);

	size_t len;
	ServiceTag tag;
};
}

#endif //QRPC_MSGPACKAGE_H
