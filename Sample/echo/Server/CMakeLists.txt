cmake_minimum_required(VERSION 3.15)
project(server-sample)

include_directories(../../..)

add_executable(${PROJECT_NAME}
        ../../../Server/Reactor/EpollImplement/EpollEvents.h ../../../Server/Reactor/EpollImplement/EpollReactorImplementation.h ../../../Server/Reactor/EpollImplement/EpollReactorImplementation.cpp ../../../Server/Reactor/EpollImplement/Handlers/ListeningHandler.h ../../../Server/Reactor/EpollImplement/Handlers/ListeningHandler.cpp ../../../Server/Reactor/EpollImplement/Handlers/SocketHandler.h ../../../Server/Reactor/EpollImplement/Handlers/SocketHandler.cpp
        ../../../Server/Reactor/EventHandler.h ../../../Server/Reactor/EventType.h ../../../impl/Handle.h ../../../Server/Reactor/Reactor.hpp
        ../../../CodeGen/Msg.h ../../../CodeGen/Msg.cpp
        main.cpp
        ../../../impl/ReaderWriterImplement.cpp ../../../impl/ReaderWriterImplement.h ../../../impl/ReaderWriter.h ../../../Server/Server.cpp ../../../Server/Server.h ../../../Server/ServerBuilder.cpp ../../../Server/ServerBuilder.h ../../../CodeGen/Service.cpp ../../../CodeGen/Service.h ../msg/ServiceGen.cpp ../msg/ServiceGen.h ../msg/MsgGen.cpp ../msg/MsgGen.h ../../../CodeGen/MethodWrapper.cpp ../../../CodeGen/MethodWrapper.h ../../../impl/ByteBuf.cpp ../../../impl/ByteBuf.h ../../../Client/Connection.cpp ../../../Client/Connection.h ../../../Client/Call.cpp ../../../Client/Call.h)

target_link_libraries(${PROJECT_NAME} pthread)