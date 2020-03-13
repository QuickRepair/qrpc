cmake_minimum_required(VERSION 3.15)
project(client-sample)

include_directories(../../..)

add_executable(${PROJECT_NAME}
        ../../../include/server/reactor/epoll/EpollEvents.h ../../../include/server/reactor/epoll/EpollReactorImplementation.h ../../../src/server/reactor/epoll/EpollReactorImplementation.cpp ../../../include/server/reactor/epoll/handlers/ListeningHandler.h ../../../src/server/reactor/epoll/handlers/ListeningHandler.cpp ../../../include/server/reactor/epoll/handlers/SocketHandler.h ../../../src/server/reactor/epoll/handlers/SocketHandler.cpp
        ../../../include/server/reactor/EventHandler.h ../../../include/server/reactor/EventType.h ../../../include/impl/Handle.h ../../../include/server/reactor/Reactor.hpp
        ../../../include/code_gen/Msg.h ../../../src/code_gen/Msg.cpp
        main.cpp
        ../../../src/impl/ReaderWriterImplement.cpp ../../../include/impl/ReaderWriterImplement.h ../../../include/impl/ReaderWriter.h ../../../src/server/Server.cpp ../../../include/server/Server.h ../../../src/server/ServerBuilder.cpp ../../../include/server/ServerBuilder.h ../../../src/code_gen/Service.cpp ../../../include/code_gen/Service.h ../msg/ServiceGen.cpp ../msg/ServiceGen.h ../msg/MsgGen.cpp ../msg/MsgGen.h ../../../src/code_gen/MethodWrapper.cpp ../../../include/code_gen/MethodWrapper.h ../../../src/impl/ByteBuf.cpp ../../../include/impl/ByteBuf.h ../../../src/client/Connection.cpp ../../../include/client/Connection.h ../../../src/client/Call.cpp ../../../include/client/Call.h ../../../src/code_gen/SDStream.cpp ../../../include/code_gen/SDStream.h ../../../src/code_gen/Serializable.cpp ../../../include/code_gen/Serializable.h ../../../src/code_gen/MsgPackage.cpp ../../../include/code_gen/MsgPackage.h)

target_link_libraries(${PROJECT_NAME})