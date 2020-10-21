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
find_package(Qt5PrintSupport REQUIRED)
list(APPEND LIBRARIES
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Charts
        Qt5::Network
        Qt5::PrintSupport)
list(REMOVE_DUPLICATES LIBRARIES)
add_executable(Client main.cpp Packet/Message.h Packet/Message.cpp SharedEditor.h SharedEditor.cpp Packet/Symbols/Symbol.h Packet/Symbols/Symbol.cpp Packet/Symbols/SymId.h Packet/LoginInfo.cpp Packet/LoginInfo.h
        Packet/Payload.cpp Packet/Payload.h Packet/DataPacket.h Packet/DataPacket.cpp LoginDialog.cpp LoginDialog.h EditorGUI.cpp EditorGUI.h Transceiver.cpp Transceiver.h Socket.h
        Packet/StringMessages.cpp Packet/StringMessages.h RemoteCursor.cpp RemoteCursor.h Packet/Command.cpp Packet/Command.h MainWindow.cpp MainWindow.h FileSystemTreeView.cpp
        FileSystemTreeView.h MyTextEdit.cpp MyTextEdit.h Packet/CursorPosition.cpp Packet/CursorPosition.h CursorColors.h InfoWidget.cpp InfoWidget.h InfoWidgetEdit.cpp InfoWidgetEdit.h
        Packet/FileInfo.cpp Packet/FileInfo.h SignInWidget.cpp SignInWidget.h AddUserWidget.cpp AddUserWidget.h adduserwidget.ui InviteUserWidgetItem.cpp InviteUserWidgetItem.h inviteuserwidgetitem.ui
        InviteUserWidget.cpp InviteUserWidget.h inviteuserwidget.ui uriwidget.ui UriWidget.cpp UriWidget.h InfoUsersListWidget.h InfoUsersListWidget.cpp infouserslistwidget.ui
        FileSystemGridView.h FileSystemGridView.cpp FileSystemGridView.ui UsersList.cpp UsersList.h CustomStyle.cpp CustomStyle.h Packet/ErrorPacket.cpp Packet/ErrorPacket.h)
target_link_libraries(Client ${LIBRARIES})