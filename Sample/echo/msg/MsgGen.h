//
// Created by gaojian on 2019/12/27.
//

#ifndef MSG_H
#define MSG_H

#include "CodeGen/Msg.h"

class EchoCharRequest : public qrpc::Msg {
public:
	static constexpr qrpc::MsgTag tag = 0;

	void setMsg(char msg) { m_msg = msg; }
	char getMsg() const { return m_msg; }

	size_t byteSize() const override;
	void serialize(qrpc::ServiceSerialize *serializing) override;
	void deserialize(const char *buf) override;

	static std::unique_ptr<EchoCharRequest> create() { return std::make_unique<EchoCharRequest>(); }
private:
	char m_msg;
};

class EchoCharResponse : public qrpc::Msg {
public:
	static constexpr qrpc::MsgTag tag = 1;

	void setMsg(char msg) { m_msg = msg; }
	char getMsg() const { return m_msg; }

	size_t byteSize() const override;
	void serialize(qrpc::ServiceSerialize *serializing) override;
	void deserialize(const char *buf) override;

	static std::unique_ptr<EchoCharResponse> create() { return std::make_unique<EchoCharResponse>(); }
private:
	char m_msg;
};

class EchoRequestSample : public qrpc::Msg {
public:
	static constexpr qrpc::MsgTag tag = 2;

	void setMsg(std::string msg) { m_msg = msg; }
	const std::string &getMsg() const { return m_msg; }

	size_t byteSize() const override;
	void serialize(qrpc::ServiceSerialize *serializing) override;
	void deserialize(const char *buf) override;

	static std::unique_ptr<EchoRequestSample> create() { return std::make_unique<EchoRequestSample>(); }
private:
	std::string m_msg;
};

class EchoResponseSample : public qrpc::Msg {
public:
	static constexpr qrpc::MsgTag tag = 3;

	void setMsg(std::string msg) { m_msg = msg; }
	const std::string &getMsg() const { return m_msg; }

	size_t byteSize() const override;
	void serialize(qrpc::ServiceSerialize *serializing) override;
	void deserialize(const char *buf) override;

	static std::unique_ptr<EchoResponseSample> create() { return std::make_unique<EchoResponseSample>(); }
private:
	std::string m_msg;
};

#endif //QRPC_MSG_H
