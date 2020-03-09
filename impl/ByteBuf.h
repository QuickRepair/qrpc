//
// Created by gaojian on 2019/12/28.
//

#ifndef QRPC_BYTEBUF_H
#define QRPC_BYTEBUF_H

#include <memory>
#include <string>
#include <optional>
#include "CodeGen/Service.h"

namespace qrpc {

class Service;
class Msg;
class MsgRepository;
class RequestReader;
class ResponseWriter;

/// @brief: data to be transferred
// Todo: buf should allocated by memory pool
struct ByteBuf {
	explicit ByteBuf(size_t bufSize = BUF_SIZE);
	~ByteBuf();

	static constexpr size_t BUF_SIZE = 1024;
	size_t size;
	char *msg_buff;
};

/// @brief: ByteBufMaker: [string | int] -> ByteBuf
/// use this to convert Msg to ByteBuf
class ServiceSerialize {
public:
	std::unique_ptr<ByteBuf> serialize(ServiceTag serviceTage, Msg *msg);

	void writeChar(const char data);

private:
	std::unique_ptr<ByteBuf> allocaMem(size_t size);

	size_t m_size;
	size_t m_cursor;
	ByteBuf *_buf;
};

/// @brief: ByteBufDeserialize: ByteBuf -> {ServiceTag & Msg}
/// get Service and Msg from an incoming message
class ByteBufDeserialize {
public:
	explicit ByteBufDeserialize(MsgRepository *repository);
	struct ServiceOut {
		ServiceTag serviceTag;
		std::unique_ptr<Msg> request;
		std::unique_ptr<Msg> response;
	};
	std::optional<ServiceOut> deserializeRequest(const ByteBuf *recvBuf);
	static void deserializeResponse(const ByteBuf *recvBuf, Msg *response);
private:
	MsgRepository *_repository;
};

/// @brief: HandleRequest: request -> response
/// get response from incoming message
class HandleRequest {
public:
	HandleRequest(Service *service, MsgRepository *repository);
	/// @brief Return response
	std::unique_ptr<ByteBuf> process(const ByteBuf *buf);

private:
	ByteBufDeserialize convert;
	Service *_service;
};
}

#endif //QRPC_BYTEBUF_H
