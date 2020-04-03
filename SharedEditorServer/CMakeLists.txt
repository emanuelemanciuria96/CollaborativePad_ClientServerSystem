cmake_minimum_required(VERSION 3.14)
project(SharedEditorServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Charts REQUIRED)
find_package(Qt5Network REQUIRED)
list(APPEND LIBRARIES
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Charts
        Qt5::Network)
list(REMOVE_DUPLICATES LIBRARIES)
add_executable(SharedEditorServer main.cpp NetworkServer.cpp NetworkServer.h Packet/Symbols/Symbol.cpp Packet/Symbols/Symbol.h Packet/Symbols/SymId.cpp Packet/Symbols/SymId.h ServerThread.cpp ServerThread.h
        Packet/Message.cpp Packet/Message.h Packet/DataPacket.cpp Packet/DataPacket.h Packet/Payload.cpp Packet/Payload.h Packet/LoginInfo.cpp Packet/LoginInfo.h MessageHandler.cpp MessageHandler.h jsoncpp.cpp json/json-forwards.h json/json.h Packet/Command.cpp Packet/Command.h Socket.h)
target_link_libraries(SharedEditorServer ${LIBRARIES})