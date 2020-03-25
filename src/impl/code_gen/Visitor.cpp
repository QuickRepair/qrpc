//
// Created by gaojian on 2020/3/24.
//

#include "impl/code_gen/Visitor.h"
#include "impl/code_gen/AST.hpp"
#include "impl/code_gen/SymbolTable.hpp"
#include "impl/code_gen/CodeGenTemplate.h"
#include "impl/code_gen/TypeMap.h"
#include "impl/code_gen/Stream.h"

using std::make_shared;
using qrpc::CodeGen::AST::Type;
using namespace qrpc::CodeGen::ST;

namespace qrpc::CodeGen::Visitor {
ASTBuildVisitor::ASTBuildVisitor(qrpc::CodeGen::ST::SymbolTable *context)
	: _STContext{context}
{}

void ASTBuildVisitor::visitContext(qrpc::CodeGen::AST::ASTContext &ast)
{
	// Must build message symbol table first
	for (auto &message : ast.messages)
		visitMessageAST(message);
	for (auto &service : ast.services)
		visitServiceAST(service);
}

void ASTBuildVisitor::visitServiceAST(qrpc::CodeGen::AST::ServiceAST &ast)
{
	_STContext->insert(ast.serviceName, Type::Service);
	auto requestLookUp = _STContext->lookup(ast.requestName);
	if(!requestLookUp || requestLookUp != Type::Message)
		throw;	// TODO
	auto responseLookUp = _STContext->lookup(ast.requestName);
	if(!responseLookUp || responseLookUp != Type::Message)
		throw;	// TODO
}

void ASTBuildVisitor::visitMessageAST(qrpc::CodeGen::AST::MessageAST &ast)
{
	_STContext->insert(ast.messageName, Type::Message);
	auto tmp = _STContext;
	_STContext = dynamic_cast<STRoot *>(_STContext)->newBlock();
	for (auto &attr : ast.def)
		visitMessageAttr(attr);
	_STContext = tmp;
}

void ASTBuildVisitor::visitMessageAttr(qrpc::CodeGen::AST::MessageAttrDefAST &ast)
{
	_STContext->insert(ast.attrName, Type::MessageAttr);
}

PrintVisitor::PrintVisitor(std::ostream &os)
	: ostream{os}
{}

void PrintVisitor::visitContext(qrpc::CodeGen::AST::ASTContext &ast)
{
	for (auto &service : ast.services)
		visitServiceAST(service);
	for (auto &message : ast.messages)
		visitMessageAST(message);
}

void PrintVisitor::visitServiceAST(qrpc::CodeGen::AST::ServiceAST &ast)
{
	ostream << "Service define" << std::endl;
	ostream << "Name: " << ast.serviceName << " Request: " << ast.requestName << " Response: " << ast.responseName;
	ostream << std::endl << "--------------" << std::endl;
}

void PrintVisitor::visitMessageAST(qrpc::CodeGen::AST::MessageAST &ast)
{
	ostream << "Message define" << std::endl;
	ostream << "Name: " << ast.messageName << std::endl;
	ostream << "Attr: ";
	for (auto &attr : ast.def)
		visitMessageAttr(attr);
	ostream << std::endl << "--------------" << std::endl;
}

void PrintVisitor::visitMessageAttr(qrpc::CodeGen::AST::MessageAttrDefAST &ast)
{
	ostream << ast.type << "(" << ast.attrName << ") ";
}

CodeGenVisitor::CodeGenVisitor(OutputStream &serviceHeader, OutputStream &serviceSource, OutputStream &messageHeader, OutputStream &messageSource)
	: serviceHeaderOStream{serviceHeader}, serviceSourceOStream{serviceSource},
	messageHeaderOStream{messageHeader}, messageSourceOStream{messageSource},
	codeTemplate{make_shared<CodeTemplate::CPPCodeGen>()},
	typeMap{make_shared<QRPCType::TypeMap>()},
	serializeMap{make_shared<QRPCType::SerializeTypeMap>()}
{}

void CodeGenVisitor::visitContext(qrpc::CodeGen::AST::ASTContext &ast)
{
	for (auto &service : ast.services)
		visitServiceAST(service);
	for (auto &message : ast.messages)
		visitMessageAST(message);
	serviceHeaderOStream.getStream() << codeTemplate->getServiceHeader(messageHeaderOStream.getName());
	serviceSourceOStream.getStream() << codeTemplate->getServiceSource(serviceHeaderOStream.getName());
	messageHeaderOStream.getStream() << codeTemplate->getMessageHeader();
	messageSourceOStream.getStream() << codeTemplate->getMessageSource(messageHeaderOStream.getName());
}

void CodeGenVisitor::visitServiceAST(qrpc::CodeGen::AST::ServiceAST &ast)
{
	codeTemplate->renderServiceHeader(ast.serviceName, ast.requestName, ast.responseName);
	codeTemplate->renderServiceSource(ast.serviceName, ast.requestName, ast.responseName);
}

void CodeGenVisitor::visitMessageAST(qrpc::CodeGen::AST::MessageAST &ast)
{
	for (auto &attr : ast.def)
		visitMessageAttr(attr);
	codeTemplate->doneMessageClassHeaderRender(ast.messageName);
	codeTemplate->doneMessageClassSourceRender(ast.messageName);
}

void CodeGenVisitor::visitMessageAttr(qrpc::CodeGen::AST::MessageAttrDefAST &ast)
{
	codeTemplate->renderMessageClassPropertyHeader(typeMap->get(ast.type), ast.attrName);
	codeTemplate->renderMessageClassPropertySource(serializeMap->get(ast.type), ast.attrName);
}
}
