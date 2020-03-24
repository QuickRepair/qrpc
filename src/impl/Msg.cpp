#include "impl/Msg.h"
#include "impl/MethodWrapper.h"

using std::make_unique;			using std::make_tuple;

namespace qrpc {
MsgRepository::MsgRepository()
{}

void MsgRepository::registerServiceTagPair(ServiceTag serviceTag, MsgTag requestTag, MsgTag responseTag)
{
	if (m_msgTag.size() < serviceTag + 1)
		m_msgTag.resize(serviceTag + 1);
	m_msgTag[serviceTag] = make_tuple(requestTag, responseTag);
}

void MsgRepository::addCreator(std::unique_ptr<MessageCreator> creator, MsgTag tag)
{
	if (m_repository.size() < tag + 1)
		m_repository.resize(tag + 1);
	m_repository[tag] = std::move(creator);
}

std::unique_ptr<Msg> MsgRepository::create(MsgTag tag) const
{
	return m_repository[tag]->create();
}

MsgTag MsgRepository::getRequestTag(ServiceTag tag) const
{
	return std::get<0>(m_msgTag[tag]);
}

MsgTag MsgRepository::getResponseTag(ServiceTag tag) const
{
	return std::get<1>(m_msgTag[tag]);
}
}
