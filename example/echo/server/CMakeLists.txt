cmake_minimum_required(VERSION 3.15)
project(server-sample)

include_directories(../../..)
include_directories(${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME}
        ../../../include/server/reactor/epoll/EpollEvents.h ../../../include/server/reactor/epoll/EpollReactorImplementation.h ../../../src/server/reactor/epoll/EpollReactorImplementation.cpp ../../../include/server/reactor/epoll/handlers/ListeningHandler.h ../../../src/server/reactor/epoll/handlers/ListeningHandler.cpp ../../../include/server/reactor/epoll/handlers/SocketHandler.h ../../../src/server/reactor/epoll/handlers/SocketHandler.cpp
        ../../../include/server/reactor/EventHandler.h ../../../include/server/reactor/EventType.h ../../../include/net/Handle.h ../../../include/server/reactor/Reactor.hpp
        ../../../include/impl/Msg.h ../../../src/impl/Msg.cpp
        main.cpp
        ${CMAKE_BINARY_DIR}/test_message.cpp ${CMAKE_BINARY_DIR}/test_message.h ${CMAKE_BINARY_DIR}/test_service.h ${CMAKE_BINARY_DIR}/test_service.cpp
        ../../../src/net/ReaderWriterImplement.cpp ../../../include/net/ReaderWriterImplement.h ../../../include/net/ReaderWriter.h ../../../src/server/Server.cpp ../../../include/server/Server.h ../../../src/server/ServerBuilder.cpp ../../../include/server/ServerBuilder.h ../../../src/impl/Service.cpp ../../../include/impl/Service.h ../../../src/impl/MethodWrapper.cpp ../../../include/impl/MethodWrapper.h ../../../src/net/ByteBuf.cpp ../../../include/net/ByteBuf.h ../../../src/client/Connection.cpp ../../../include/client/Connection.h ../../../src/client/Call.cpp ../../../include/client/Call.h ../../../src/impl/SDStream.cpp ../../../include/impl/SDStream.h ../../../src/impl/Serializable.cpp ../../../include/impl/Serializable.h ../../../src/impl/MsgPackage.cpp ../../../include/impl/MsgPackage.h ../../../src/support/ThreadBase.cpp ../../../include/support/ThreadBase.hpp ../../../src/support/ThreadPool.cpp ../../../include/support/ThreadPool.hpp)

target_link_libraries(${PROJECT_NAME} pthread)