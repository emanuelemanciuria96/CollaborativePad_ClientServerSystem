cmake_minimum_required(VERSION 3.14)
project(Client)

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
add_executable(Client main.cpp Packet/Message.h Packet/Message.cpp SharedEditor.h SharedEditor.cpp Packet/Symbols/Symbol.h Packet/Symbols/Symbol.cpp Packet/Symbols/SymId.h Packet/LoginInfo.cpp Packet/LoginInfo.h
        Packet/Payload.cpp Packet/Payload.h Packet/DataPacket.h Packet/DataPacket.cpp LoginDialog.cpp LoginDialog.h EditorGUI.cpp EditorGUI.h Packet/Command.cpp Packet/Command.h)
target_link_libraries(Client ${LIBRARIES})