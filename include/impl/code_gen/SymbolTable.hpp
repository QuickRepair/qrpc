//
// Created by gaojian on 2020/3/24.
//

#ifndef QGEN_SYMBOLTABLE_HPP
#define QGEN_SYMBOLTABLE_HPP

#include <unordered_map>
#include <vector>
#include <memory>
#include <optional>

namespace qrpc::CodeGen::AST {
enum class Type;
}

namespace qrpc::CodeGen::ST {

class SymbolTable {
public:
	virtual ~SymbolTable() = default;

	virtual void insert(const std::string &name, qrpc::CodeGen::AST::Type type) = 0;
	virtual std::optional<qrpc::CodeGen::AST::Type> lookup(const std::string &name) = 0;
};

class STRoot : public SymbolTable {
public:
	void insert(const std::string &name, qrpc::CodeGen::AST::Type type) override;
	std::optional<qrpc::CodeGen::AST::Type> lookup(const std::string &name) override;

	SymbolTable *newBlock();

private:
	std::unordered_map<std::string, qrpc::CodeGen::AST::Type> map;
	std::vector<std::unique_ptr<SymbolTable>> st;
};

class MessageST : public SymbolTable {
public:
	void insert(const std::string &name, qrpc::CodeGen::AST::Type type) override;
	std::optional<qrpc::CodeGen::AST::Type> lookup(const std::string &name) override;

private:
	std::unordered_map<std::string, qrpc::CodeGen::AST::Type> map;
};
}

#endif //QGEN_SYMBOLTABLE_HPP
