cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)

project(qgen)

add_executable(${PROJECT_NAME}
        include/impl/code_gen/QrpcGrammar.hpp ../src/impl/code_gen/main.cpp ../include/impl/code_gen/AST.hpp ../src/impl/code_gen/Visitor.cpp ../include/impl/code_gen/Visitor.h ../include/impl/code_gen/SymbolTable.hpp ../src/impl/code_gen/SymbolTable.cpp ../src/impl/code_gen/CodeGenTemplate.cpp ../include/impl/code_gen/CodeGenTemplate.h ../include/impl/code_gen/template/CppMessageOut.h ../src/impl/code_gen/template/CppMessageOut.cpp ../src/impl/code_gen/template/CppServiceOut.cpp ../src/impl/code_gen/TypeMap.cpp ../include/impl/code_gen/TypeMap.h ../src/impl/code_gen/ArgParse.cpp ../include/impl/code_gen/ArgParse.h ../src/impl/code_gen/Stream.cpp ../include/impl/code_gen/Stream.h)
