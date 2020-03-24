//
// Created by gaojian on 2020/3/24.
//

#ifndef QGEN_CPPMESSAGEOUT_H
#define QGEN_CPPMESSAGEOUT_H

#include <string>

namespace qrpc::CodeGen::CodeTemplate::CPP {

const std::string message_gen_hpp_setter_and_getter = R"(
void set_{%attr_name}({%type} {%attr_name}) { _{%attr_name} = {%attr_name}; }
{%type} get_{%attr_name}() const { return _{%attr_name}; }
)";
const std::string message_gen_hpp_attr = R"(
{%type} _{%attr_name};
)";
const std::string message_gen_hpp_class_def = R"(
class {%message_name} : public qrpc::Msg {
public:
	static constexpr qrpc::MsgTag tag = 0;

	{%message_gen_hpp_setter_and_getter}

	size_t byteSize() override;
	size_t serializedByteSize() override;
	void serialize(qrpc::SerializeStream &stream) override;
	void deserialize(qrpc::DeserializeStream &stream) override;

	static std::unique_ptr<{%message_name}> create() { return std::make_unique<{%message_name}>(); }
private:
	{%message_gen_hpp_attr}
};
)";
const std::string message_gen_hpp = R"(
#ifndef QRPC_CODE_GEN_MSG_H
#define QRPC_CODE_GEN_MSG_H

#include "impl/Msg.h"

{%message_gen_hpp_class_def}
#endif
)";

const std::string message_gen_cpp_include_message_h = R"(
#include "{%message_gen_h_file}"
)";
const std::string message_gen_cpp_byte_size_def = R"(
{%serialize_class} {%attr_name}(_{%attr_name});
byteSizeLong += {%attr_name}.byteSize();
)";
const std::string message_gen_cpp_serialize_byte_size_def = R"(
{%serialize_class} {%attr_name}(_{%attr_name});
byteSizeLong += {%attr_name}.serializedByteSize();
)";
const std::string message_gen_cpp_serialize_def = R"(
{%serialize_class} {%attr_name}(_{%attr_name});
{%attr_name}.serialize(stream);
)";
const std::string message_gen_cpp_deserialzie_def = R"(
{%serialize_class} {%attr_name}(_{%attr_name});
{%attr_name}.deserialize(stream);
)";
const std::string message_gen_method_def = R"(
size_t {%message_name}::byteSize()
{
	size_t byteSizeLong = 0;
	{%message_gen_cpp_byte_size_def}
	return byteSizeLong;
}

size_t {%message_name}::serializedByteSize()
{
	size_t byteSizeLong = 0;
	{%message_gen_cpp_serialize_byte_size_def}
	return byteSizeLong;
}

void {%message_name}::serialize(qrpc::SerializeStream &stream)
{
	{%message_gen_cpp_serialize_def}
}

void {%message_name}::deserialize(qrpc::DeserializeStream &stream)
{
	{%message_gen_cpp_deserialzie_def}
}
)";
const std::string message_gen_cpp = R"(
{%message_gen_cpp_include_message_h}
#include "net/ByteBuf.h"
#include "impl/Serializable.h"

{%message_gen_method_def}
)";
}

#endif //QGEN_CPPMESSAGEOUT_H
