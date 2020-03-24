//
// Created by gaojian on 2019/12/28.
//

#ifndef QRPC_BYTEBUF_H
#define QRPC_BYTEBUF_H

#include <memory>
#include <string>
#include <optional>
#include "impl/Service.h"

namespace qrpc {

class Service;
class Msg;
class MsgRepository;
class RequestReader;
class ResponseWriter;

/// @brief: data to be transferred
// Todo: buf should allocated by memory pool
struct ByteBuf {
	ByteBuf(ByteBuf &) = delete;
	ByteBuf(const ByteBuf &) = delete;
	explicit ByteBuf(size_t bufSize);
	ByteBuf(ByteBuf &&) noexcept;
//	ByteBuf(const ByteBuf &&) noexcept;
	~ByteBuf();

	ByteBuf &operator=(ByteBuf &) = delete;
	ByteBuf &operator=(const ByteBuf &) = delete;

	static constexpr size_t DEFAULT_BUF_SIZE = 1024;
	// TODO: max size is limited
	size_t size;
	char *msg_buff;
};

/// @brief: ByteBufMaker: [string | int] -> ByteBuf
/// use this to convert Msg to ByteBuf
/*class ServiceSerialize {
public:
	std::unique_ptr<ByteBuf> serialize(ServiceTag serviceTag, Msg *msg);

	void writeChar(const char data);
	void writeString(const std::string &str);
	void writeInt32(const int data);

private:
	std::unique_ptr<ByteBuf> allocaMem(size_t size);

	size_t m_size;
	size_t m_cursor;
	ByteBuf *_buf;
};*/

/// @brief: ByteBufDeserialize: ByteBuf -> {ServiceTag & Msg}
/// get Service and Msg from an incoming message
/*class ByteBufDeserialize {
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
};*/

/// @brief: HandleRequest: request -> response
/// get response from incoming message
class HandleRequest {
public:
	HandleRequest(Service *service, MsgRepository *repository);
	/// @brief Return response
	std::shared_ptr<ByteBuf> process(std::shared_ptr<ByteBuf> buf);

private:
	Service *_service;
	MsgRepository *_repository;
};
}

#endif //QRPC_BYTEBUF_H
