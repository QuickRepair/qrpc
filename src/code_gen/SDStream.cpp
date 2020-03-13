//
// Created by gaojian on 2020/3/11.
//

#include <code_gen/MsgPackage.h>
#include "code_gen/SDStream.h"

using std::make_unique;

namespace qrpc {
SerializeStream::SerializeStream(size_t msgSize)
		: cursor{0}
{
	buf = make_unique<ByteBuf>(msgSize);
}

SerializeStream::SerializeStream(SerializeStream &&other) noexcept
	: buf{std::move(other.buf)}, cursor{other.cursor}
{}

ByteBuf * SerializeStream::get()
{
	return buf.get();
}

std::unique_ptr<ByteBuf> SerializeStream::release()
{
	return std::move(buf);
}

DeserializeStream::DeserializeStream(std::unique_ptr<ByteBuf> &&byteBuf)
		: buf{std::move(byteBuf)}, cursor{0}
{}

ByteBuf * DeserializeStream::get() const
{
	return buf.get();
}

SerializeStream &operator<<(SerializeStream &stream, std::shared_ptr<ByteBuf> buf)
{
	stream.buf->msg_buff[stream.cursor++] = buf->size;
	for (size_t i = 0; i < buf->size; ++i)
		stream.buf->msg_buff[stream.cursor++] = buf->msg_buff[i];
	return stream;
}

SerializeStream &operator<<(SerializeStream &stream, Header &header)
{
	stream.buf->msg_buff[stream.cursor] = header.len;
	stream.cursor += sizeof(ByteBuf::size);
	stream.buf->msg_buff[stream.cursor] = header.tag;
	stream.cursor += sizeof(ServiceTag);
	return stream;
}

DeserializeStream &operator>>(DeserializeStream &stream, std::shared_ptr<ByteBuf> &buf)
{
	buf = std::make_unique<ByteBuf>(stream.buf->msg_buff[stream.cursor++]);
	for (size_t i = 0; i < buf->size; ++i)
		buf->msg_buff[i] = stream.buf->msg_buff[stream.cursor++];
	return stream;
}

DeserializeStream &operator>>(DeserializeStream &stream, Header &header)
{
	header.tag = stream.buf->msg_buff[stream.cursor];
	stream.cursor += sizeof(ServiceTag);
	return stream;
}
}
