//
// Created by gaojian on 2020/3/11.
//

#ifndef QRPC_SDSTREAM_H
#define QRPC_SDSTREAM_H

#include <cstddef>
#include <string>
#include <vector>
#include <memory>
#include "impl/ByteBuf.h"

namespace qrpc {

class Header;

class SerializeStream {
	friend SerializeStream &operator<<(SerializeStream &stream, std::shared_ptr<ByteBuf> buf);
	friend SerializeStream &operator<<(SerializeStream &stream, Header &buf);

public:
	SerializeStream(SerializeStream &) = delete;
	SerializeStream(const SerializeStream &) = delete;
	SerializeStream(const SerializeStream &&other) = delete;
	SerializeStream &operator=(SerializeStream &) = delete;
	SerializeStream &operator=(const SerializeStream &) = delete;

	explicit SerializeStream(size_t msgSize);
	SerializeStream(SerializeStream &&other) noexcept;
	std::shared_ptr<ByteBuf> get();

private:
	std::shared_ptr<ByteBuf> buf;
	size_t cursor;
};

class DeserializeStream {
	friend DeserializeStream &operator>>(DeserializeStream &stream, std::shared_ptr<ByteBuf> &buf);
	friend DeserializeStream &operator>>(DeserializeStream &stream, Header &buf);

public:
	DeserializeStream(DeserializeStream &) = delete;
	DeserializeStream(const DeserializeStream &) = delete;
	DeserializeStream &operator=(DeserializeStream &) = delete;
	DeserializeStream &operator=(const DeserializeStream &) = delete;

	explicit DeserializeStream(std::shared_ptr<ByteBuf> byteBuf);
	std::shared_ptr<ByteBuf> get() const;

private:
	std::shared_ptr<ByteBuf> buf;
	size_t cursor;
};

/// @note: SerializeStream will FREE char * after not more needed
SerializeStream &operator<<(SerializeStream &stream, std::shared_ptr<ByteBuf> buf);
SerializeStream &operator<<(SerializeStream &stream, Header &buf);
/// @note: char * is available BEFORE DeserializeStream is destroyed
DeserializeStream &operator>>(DeserializeStream &stream, std::shared_ptr<ByteBuf> &buf);
DeserializeStream &operator>>(DeserializeStream &stream, Header &buf);
}

#endif //QRPC_SDSTREAM_H
