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
find_package(Qt5Sql REQUIRED)
list(APPEND LIBRARIES
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Charts
        Qt5::Network
        Qt5::Sql)
list(REMOVE_DUPLICATES LIBRARIES)
add_executable(SharedEditorServer main.cpp NetworkServer.cpp NetworkServer.h Packet/Symbols/Symbol.h Packet/Symbols/SymId.h ServerThread.cpp ServerThread.h
        Packet/Message.h Packet/DataPacket.cpp Packet/DataPacket.h Packet/Payload.h Packet/LoginInfo.cpp Packet/LoginInfo.h MessageHandler.cpp MessageHandler.h Packet/Command.cpp Packet/Command.h Packet/StringMessages.h Packet/StringMessages.cpp Socket.h database/DBSql.cpp database/DBSql.h database/sqlite3.c database/sqlite3ext.h database/sqlite3.h database/shell.c Files.cpp Files.h SocketsPool.cpp SocketsPool.h
        Packet/CursorPosition.cpp Packet/CursorPosition.h Packet/FileInfo.h MyExceptions/LoginException.h Packet/UserInfo.h Packet/UserInfo.cpp Packet/ErrorPacket.cpp Packet/ErrorPacket.h MyExceptions/CommandException.h MyExceptions/RenCommandException.h)
target_link_libraries(SharedEditorServer ${LIBRARIES})