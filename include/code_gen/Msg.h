#ifndef QRPC_IMPL_MSG_H
#define QRPC_IMPL_MSG_H

#include <memory>
#include <vector>
#include "MethodWrapper.h"
#include "Service.h"

namespace qrpc {

class MessageCreator;
class SerializeStream;
class DeserializeStream;

using MsgTag = unsigned;

/// @brief Msg interface
class Msg {
public:
	virtual ~Msg() = default;

	virtual size_t byteSize() = 0;
	virtual size_t serializedByteSize() = 0;
	virtual void serialize(SerializeStream &stream) = 0;
	virtual void deserialize(DeserializeStream &stream) = 0;
	/// @note The following member must manually define
	/// static constexpr qrpc::MsgTag tag = %d
	/// static std::unique_ptr<SubClass> create();
};

/// @brief Store Msg creator in repository
class MsgRepository {
public:
	MsgRepository();
	void registerServiceTagPair(ServiceTag serviceTag, MsgTag requestTag, MsgTag responseTag);
	void addCreator(std::unique_ptr<MessageCreator> creator, MsgTag tag);
	MsgTag getRequestTag(ServiceTag tag) const;
	MsgTag getResponseTag(ServiceTag tag) const;
	std::unique_ptr<Msg> create(MsgTag tag) const;

private:
	/// @brief: use msg tag as index, save msg create method
	std::vector<std::unique_ptr<MessageCreator>> m_repository;
	/// @brief: use service tag as index, store this service's request/response
	std::vector<std::tuple<MsgTag, MsgTag>> m_msgTag;
};
}

#endif
