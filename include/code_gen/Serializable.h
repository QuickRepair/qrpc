//
// Created by gaojian on 2020/3/11.
//

#ifndef QRPC_SERIALIZABLE_H
#define QRPC_SERIALIZABLE_H

#include <cstddef>
#include <string>
#include "SDStream.h"

namespace qrpc {

class SerializeStream;
class DeserializeStream;

template<typename BaseType>
class Serializable {
public:
	Serializable() : baseTypeSize{sizeof(BaseType) / sizeof(char)}
	{}

	explicit Serializable(size_t size)
			: baseTypeSize{size}
	{}

	virtual ~Serializable() = default;

	virtual void serialize(SerializeStream &stream) const = 0;

	virtual void deserialize(DeserializeStream &stream) = 0;

	virtual size_t byteSize() const final
	{ return baseTypeSize; }

	virtual size_t serializedByteSize() const final
	{ return baseTypeSize + sizeof(size_t); }

protected:
	virtual std::shared_ptr<ByteBuf> toStream(BaseType &value) const = 0;

	virtual BaseType toVal(std::shared_ptr<ByteBuf> buf) const = 0;

	size_t baseTypeSize;
};

/// qrpc Build in types
template<typename BaseType>
class BuildInSerialize : public Serializable<BaseType> {
public:
	explicit BuildInSerialize(BaseType &v)
			: Serializable<BaseType>(), val{v}
	{}

	BuildInSerialize(BaseType &v, size_t size)
			: Serializable<BaseType>(size), val{v}
	{}

	~BuildInSerialize() override = default;

	void serialize(SerializeStream &stream) const final
	{
		stream << this->toStream(val);
	}

	void deserialize(DeserializeStream &stream) final
	{
		std::shared_ptr<ByteBuf> buf;
		stream >> buf;
		val = this->toVal(buf);
	}

private:
	BaseType &val;
};

template<typename BaseType = char>
class CharSerialize : public BuildInSerialize<BaseType> {
public:
	explicit CharSerialize(BaseType &v)
			: BuildInSerialize<BaseType>(v)
	{}

	~CharSerialize() final = default;

protected:
	std::shared_ptr<ByteBuf> toStream(BaseType &value) const override
	{
		std::shared_ptr<ByteBuf> buf = std::make_shared<ByteBuf>(this->baseTypeSize);
		buf->msg_buff[0] = value;
		return buf;
	}

	BaseType toVal(std::shared_ptr<ByteBuf> buf) const override
	{
		return buf->msg_buff[0];
	}
};

template<typename BaseType = std::string>
class StringSerialize : public BuildInSerialize<BaseType> {
public:
	explicit StringSerialize(BaseType &str)
		: BuildInSerialize<BaseType>(str, str.length() + 1)
	{}
	~StringSerialize() final = default;

protected:
	std::shared_ptr<ByteBuf> toStream(BaseType &value) const override
	{
		std::shared_ptr<ByteBuf> buf = std::make_shared<ByteBuf>(this->baseTypeSize);
		for (int i = 0; i < value.length(); ++i)
			buf->msg_buff[i] = value[i];
		return buf;
	}

	BaseType toVal(std::shared_ptr<ByteBuf> buf) const override
	{
		return buf->msg_buff;
	}
};

template<typename BaseType = unsigned>
class UnsignedSerialize : public BuildInSerialize<BaseType> {
public:
	explicit UnsignedSerialize(BaseType &val)
		: BuildInSerialize<BaseType>(val)
	{}
	~UnsignedSerialize() = default;

protected:
	std::shared_ptr<ByteBuf> toStream(BaseType &value) const override
	{
		std::shared_ptr<ByteBuf> buf = std::make_shared<ByteBuf>(this->baseTypeSize);
		for (int i = 0; i < this->baseTypeSize; ++i)
			buf->msg_buff[i] = value >> ((this->baseTypeSize - 1 - i) * 8);
		return buf;
	}

	BaseType toVal(std::shared_ptr<ByteBuf> buf) const override
	{
		BaseType val;
		// TODO
		val = buf->msg_buff[0];
		return val;
	}
};

template<int &val>
class IntSerialize : public Serializable<int> {
public:
	~IntSerialize() final = default;
};
}

#endif //QRPC_SERIALIZABLE_H
