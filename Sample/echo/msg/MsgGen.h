//
// Created by gaojian on 2019/12/27.
//

#ifndef MSG_H
#define MSG_H

#include "CodeGen/Msg.h"

class EchoRequest : public qrpc::Msg {
public:
	static constexpr qrpc::MsgTag tag = 0;

	void setMsg(char msg) { m_msg = msg; }
	char getMsg() const { return m_msg; }

	size_t byteSize() const override;
	void serialize(qrpc::ServiceSerialize *serializing) override;
	void deserialize(const char *buf) override;

	static std::unique_ptr<EchoRequest> create() { return std::make_unique<EchoRequest>(); }
private:
	char m_msg;
};

class EchoResponse : public qrpc::Msg {
public:
	static constexpr qrpc::MsgTag tag = 1;

	void setMsg(char msg) { m_msg = msg; }
	char getMsg() const { return m_msg; }

	size_t byteSize() const override;
	void serialize(qrpc::ServiceSerialize *serializing) override;
	void deserialize(const char *buf) override;

	static std::unique_ptr<EchoResponse> create() { return std::make_unique<EchoResponse>(); }
private:
	char m_msg;
};

class EchoRequestSample : public qrpc::Msg {
public:
	static constexpr qrpc::MsgTag tag = 2;

	void setMsg(char msg) { m_msg = msg; }
	char getMsg() const { return m_msg; }

	size_t byteSize() const override;
	void serialize(qrpc::ServiceSerialize *serializing) override;
	void deserialize(const char *buf) override;

	static std::unique_ptr<EchoRequestSample> create() { return std::make_unique<EchoRequestSample>(); }
private:
	char m_msg;
};

class EchoResponseSample : public qrpc::Msg {
public:
	static constexpr qrpc::MsgTag tag = 3;

	void setMsg(char msg) { m_msg = msg; }
	char getMsg() const { return m_msg; }

	size_t byteSize() const override;
	void serialize(qrpc::ServiceSerialize *serializing) override;
	void deserialize(const char *buf) override;

	static std::unique_ptr<EchoResponseSample> create() { return std::make_unique<EchoResponseSample>(); }
private:
	char m_msg;
};

#endif //QRPC_MSG_H
