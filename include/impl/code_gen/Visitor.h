//
// Created by gaojian on 2020/3/24.
//

#ifndef QGEN_VISITOR_H
#define QGEN_VISITOR_H

#include <ostream>

namespace qrpc::CodeGen::AST {
class ASTContext;
class ServiceAST;
class MessageAST;
class MessageAttrDefAST;
}
namespace qrpc::CodeGen::ST {
class SymbolTable;
}

namespace qrpc::CodeGen::Visitor {
class Visitor {
public:
	virtual ~Visitor() = default;
	virtual void visitContext(qrpc::CodeGen::AST::ASTContext &ast) = 0;
	virtual void visitServiceAST(qrpc::CodeGen::AST::ServiceAST &ast) = 0;
	virtual void visitMessageAST(qrpc::CodeGen::AST::MessageAST &ast) = 0;
	virtual void visitMessageAttr(qrpc::CodeGen::AST::MessageAttrDefAST &ast) = 0;
};

class ASTBuildVisitor : Visitor {
public:
	explicit ASTBuildVisitor(qrpc::CodeGen::ST::SymbolTable *context);
	void visitContext(qrpc::CodeGen::AST::ASTContext &ast) override;
	void visitServiceAST(qrpc::CodeGen::AST::ServiceAST &ast) override;
	void visitMessageAST(qrpc::CodeGen::AST::MessageAST &ast) override;
	void visitMessageAttr(qrpc::CodeGen::AST::MessageAttrDefAST &ast) override;

private:
	qrpc::CodeGen::ST::SymbolTable *_STContext;
};

class PrintVisitor : Visitor {
public:
	PrintVisitor(std::ostream &os);
	void visitContext(qrpc::CodeGen::AST::ASTContext &ast) override;
	void visitServiceAST(qrpc::CodeGen::AST::ServiceAST &ast) override;
	void visitMessageAST(qrpc::CodeGen::AST::MessageAST &ast) override;
	void visitMessageAttr(qrpc::CodeGen::AST::MessageAttrDefAST &ast) override;

private:
	std::ostream &ostream;
};

class CodeGenVisitor : Visitor {
public:
	CodeGenVisitor(std::ostream &serviceOut, std::ostream &messageOut);
	void visitContext(qrpc::CodeGen::AST::ASTContext &ast) override;
	void visitServiceAST(qrpc::CodeGen::AST::ServiceAST &ast) override;
	void visitMessageAST(qrpc::CodeGen::AST::MessageAST &ast) override;
	void visitMessageAttr(qrpc::CodeGen::AST::MessageAttrDefAST &ast) override;

private:
	std::ostream &ostream;
};
}

#endif //QGEN_VISITOR_H
