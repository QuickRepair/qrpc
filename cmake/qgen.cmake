cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)

project(qgen)

add_executable(${PROJECT_NAME}
        include/impl/code_gen/QrpcGrammar.hpp ../src/impl/code_gen/main.cpp ../include/impl/code_gen/AST.hpp ../src/impl/code_gen/Visitor.cpp ../include/impl/code_gen/Visitor.h ../include/impl/code_gen/SymbolTable.hpp ../src/impl/code_gen/SymbolTable.cpp ../src/impl/code_gen/CodeGenTemplate.cpp ../include/impl/code_gen/CodeGenTemplate.h ../include/impl/code_gen/template/CppMessageOut.h)
