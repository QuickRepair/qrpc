//
// Created by gaojian on 2020/3/24.
//

#include "impl/code_gen/SymbolTable.hpp"

using std::make_unique;

namespace qrpc::CodeGen::ST {
void STRoot::insert(const std::string &name, qrpc::CodeGen::AST::Type type)
{
	if (map.find(name) == map.end())
		map[name] = type;
	else
		throw;	//TODO
}

std::optional<qrpc::CodeGen::AST::Type> STRoot::lookup(const std::string &name)
{
	auto it =  map.find(name);
	if (it == map.end())
		return std::nullopt;
	else
		return it->second;
}

SymbolTable * STRoot::newBlock()
{
	auto block = make_unique<MessageST>();
	MessageST *ptr = block.get();
	st.emplace_back(std::move(block));
	return ptr;
}

void MessageST::insert(const std::string &name, qrpc::CodeGen::AST::Type type)
{
	if (map.find(name) == map.end())
		map[name] = type;
	else
		throw;	//TODO
}

std::optional<qrpc::CodeGen::AST::Type> MessageST::lookup(const std::string &name)
{
	auto it =  map.find(name);
	if (it == map.end())
		return std::nullopt;
	else
		return it->second;
}
}
