# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Program Files (x86)\CLion 2019.2.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Program Files (x86)\CLion 2019.2.1\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "D:\poliTO\magistrale\Programmazione di Sistema\Malnati\laboratori\progetto\SharedEditorServer"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "D:\poliTO\magistrale\Programmazione di Sistema\Malnati\laboratori\progetto\SharedEditorServer\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/SharedEditorServer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SharedEditorServer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SharedEditorServer.dir/flags.make

CMakeFiles/SharedEditorServer.dir/SharedEditorServer_autogen/mocs_compilation.cpp.obj: CMakeFiles/SharedEditorServer.dir/flags.make
CMakeFiles/SharedEditorServer.dir/SharedEditorServer_autogen/mocs_compilation.cpp.obj: CMakeFiles/SharedEditorServer.dir/includes_CXX.rsp
CMakeFiles/SharedEditorServer.dir/SharedEditorServer_autogen/mocs_compilation.cpp.obj: SharedEditorServer_autogen/mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\poliTO\magistrale\Programmazione di Sistema\Malnati\laboratori\progetto\SharedEditorServer\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SharedEditorServer.dir/SharedEditorServer_autogen/mocs_compilation.cpp.obj"
	D:\PROGRA~2\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\SharedEditorServer.dir\SharedEditorServer_autogen\mocs_compilation.cpp.obj -c "D:\poliTO\magistrale\Programmazione di Sistema\Malnati\laboratori\progetto\SharedEditorServer\cmake-build-debug\SharedEditorServer_autogen\mocs_compilation.cpp"

CMakeFiles/SharedEditorServer.dir/SharedEditorServer_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SharedEditorServer.dir/SharedEditorServer_autogen/mocs_compilation.cpp.i"
	D:\PROGRA~2\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\poliTO\magistrale\Programmazione di Sistema\Malnati\laboratori\progetto\SharedEditorServer\cmake-build-debug\SharedEditorServer_autogen\mocs_compilation.cpp" > CMakeFiles\SharedEditorServer.dir\SharedEditorServer_autogen\mocs_compilation.cpp.i

CMakeFiles/SharedEditorServer.dir/SharedEditorServer_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SharedEditorServer.dir/SharedEditorServer_autogen/mocs_compilation.cpp.s"
	D:\PROGRA~2\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\poliTO\magistrale\Programmazione di Sistema\Malnati\laboratori\progetto\SharedEditorServer\cmake-build-debug\SharedEditorServer_autogen\mocs_compilation.cpp" -o CMakeFiles\SharedEditorServer.dir\SharedEditorServer_autogen\mocs_compilation.cpp.s

CMakeFiles/SharedEditorServer.dir/main.cpp.obj: CMakeFiles/SharedEditorServer.dir/flags.make
CMakeFiles/SharedEditorServer.dir/main.cpp.obj: CMakeFiles/SharedEditorServer.dir/includes_CXX.rsp
CMakeFiles/SharedEditorServer.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\poliTO\magistrale\Programmazione di Sistema\Malnati\laboratori\progetto\SharedEditorServer\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/SharedEditorServer.dir/main.cpp.obj"
	D:\PROGRA~2\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\SharedEditorServer.dir\main.cpp.obj -c "D:\poliTO\magistrale\Programmazione di Sistema\Malnati\laboratori\progetto\SharedEditorServer\main.cpp"

CMakeFiles/SharedEditorServer.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SharedEditorServer.dir/main.cpp.i"
	D:\PROGRA~2\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\poliTO\magistrale\Programmazione di Sistema\Malnati\laboratori\progetto\SharedEditorServer\main.cpp" > CMakeFiles\SharedEditorServer.dir\main.cpp.i

CMakeFiles/SharedEditorServer.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SharedEditorServer.dir/main.cpp.s"
	D:\PROGRA~2\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\poliTO\magistrale\Programmazione di Sistema\Malnati\laboratori\progetto\SharedEditorServer\main.cpp" -o CMakeFiles\SharedEditorServer.dir\main.cpp.s

CMakeFiles/SharedEditorServer.dir/NetworkServer.cpp.obj: CMakeFiles/SharedEditorServer.dir/flags.make
CMakeFiles/SharedEditorServer.dir/NetworkServer.cpp.obj: CMakeFiles/SharedEditorServer.dir/includes_CXX.rsp
CMakeFiles/SharedEditorServer.dir/NetworkServer.cpp.obj: ../NetworkServer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\poliTO\magistrale\Programmazione di Sistema\Malnati\laboratori\progetto\SharedEditorServer\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/SharedEditorServer.dir/NetworkServer.cpp.obj"
	D:\PROGRA~2\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\SharedEditorServer.dir\NetworkServer.cpp.obj -c "D:\poliTO\magistrale\Programmazione di Sistema\Malnati\laboratori\progetto\SharedEditorServer\NetworkServer.cpp"

CMakeFiles/SharedEditorServer.dir/NetworkServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SharedEditorServer.dir/NetworkServer.cpp.i"
	D:\PROGRA~2\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\poliTO\magistrale\Programmazione di Sistema\Malnati\laboratori\progetto\SharedEditorServer\NetworkServer.cpp" > CMakeFiles\SharedEditorServer.dir\NetworkServer.cpp.i

CMakeFiles/SharedEditorServer.dir/NetworkServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SharedEditorServer.dir/NetworkServer.cpp.s"
	D:\PROGRA~2\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\poliTO\magistrale\Programmazione di Sistema\Malnati\laboratori\progetto\SharedEditorServer\NetworkServer.cpp" -o CMakeFiles\SharedEditorServer.dir\NetworkServer.cpp.s

CMakeFiles/SharedEditorServer.dir/Symbol.cpp.obj: CMakeFiles/SharedEditorServer.dir/flags.make
CMakeFiles/SharedEditorServer.dir/Symbol.cpp.obj: CMakeFiles/SharedEditorServer.dir/includes_CXX.rsp
CMakeFiles/SharedEditorServer.dir/Symbol.cpp.obj: ../Symbol.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\poliTO\magistrale\Programmazione di Sistema\Malnati\laboratori\progetto\SharedEditorServer\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/SharedEditorServer.dir/Symbol.cpp.obj"
	D:\PROGRA~2\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\SharedEditorServer.dir\Symbol.cpp.obj -c "D:\poliTO\magistrale\Programmazione di Sistema\Malnati\laboratori\progetto\SharedEditorServer\Symbol.cpp"

CMakeFiles/SharedEditorServer.dir/Symbol.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SharedEditorServer.dir/Symbol.cpp.i"
	D:\PROGRA~2\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\poliTO\magistrale\Programmazione di Sistema\Malnati\laboratori\progetto\SharedEditorServer\Symbol.cpp" > CMakeFiles\SharedEditorServer.dir\Symbol.cpp.i

CMakeFiles/SharedEditorServer.dir/Symbol.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SharedEditorServer.dir/Symbol.cpp.s"
	D:\PROGRA~2\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\poliTO\magistrale\Programmazione di Sistema\Malnati\laboratori\progetto\SharedEditorServer\Symbol.cpp" -o CMakeFiles\SharedEditorServer.dir\Symbol.cpp.s

CMakeFiles/SharedEditorServer.dir/SymId.cpp.obj: CMakeFiles/SharedEditorServer.dir/flags.make
CMakeFiles/SharedEditorServer.dir/SymId.cpp.obj: CMakeFiles/SharedEditorServer.dir/includes_CXX.rsp
CMakeFiles/SharedEditorServer.dir/SymId.cpp.obj: ../SymId.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\poliTO\magistrale\Programmazione di Sistema\Malnati\laboratori\progetto\SharedEditorServer\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/SharedEditorServer.dir/SymId.cpp.obj"
	D:\PROGRA~2\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\SharedEditorServer.dir\SymId.cpp.obj -c "D:\poliTO\magistrale\Programmazione di Sistema\Malnati\laboratori\progetto\SharedEditorServer\SymId.cpp"

CMakeFiles/SharedEditorServer.dir/SymId.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SharedEditorServer.dir/SymId.cpp.i"
	D:\PROGRA~2\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\poliTO\magistrale\Programmazione di Sistema\Malnati\laboratori\progetto\SharedEditorServer\SymId.cpp" > CMakeFiles\SharedEditorServer.dir\SymId.cpp.i

CMakeFiles/SharedEditorServer.dir/SymId.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SharedEditorServer.dir/SymId.cpp.s"
	D:\PROGRA~2\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\poliTO\magistrale\Programmazione di Sistema\Malnati\laboratori\progetto\SharedEditorServer\SymId.cpp" -o CMakeFiles\SharedEditorServer.dir\SymId.cpp.s

CMakeFiles/SharedEditorServer.dir/Message.cpp.obj: CMakeFiles/SharedEditorServer.dir/flags.make
CMakeFiles/SharedEditorServer.dir/Message.cpp.obj: CMakeFiles/SharedEditorServer.dir/includes_CXX.rsp
CMakeFiles/SharedEditorServer.dir/Message.cpp.obj: ../Message.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\poliTO\magistrale\Programmazione di Sistema\Malnati\laboratori\progetto\SharedEditorServer\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/SharedEditorServer.dir/Message.cpp.obj"
	D:\PROGRA~2\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\SharedEditorServer.dir\Message.cpp.obj -c "D:\poliTO\magistrale\Programmazione di Sistema\Malnati\laboratori\progetto\SharedEditorServer\Message.cpp"

CMakeFiles/SharedEditorServer.dir/Message.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SharedEditorServer.dir/Message.cpp.i"
	D:\PROGRA~2\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\poliTO\magistrale\Programmazione di Sistema\Malnati\laboratori\progetto\SharedEditorServer\Message.cpp" > CMakeFiles\SharedEditorServer.dir\Message.cpp.i

CMakeFiles/SharedEditorServer.dir/Message.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SharedEditorServer.dir/Message.cpp.s"
	D:\PROGRA~2\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\poliTO\magistrale\Programmazione di Sistema\Malnati\laboratori\progetto\SharedEditorServer\Message.cpp" -o CMakeFiles\SharedEditorServer.dir\Message.cpp.s

CMakeFiles/SharedEditorServer.dir/ServerThread.cpp.obj: CMakeFiles/SharedEditorServer.dir/flags.make
CMakeFiles/SharedEditorServer.dir/ServerThread.cpp.obj: CMakeFiles/SharedEditorServer.dir/includes_CXX.rsp
CMakeFiles/SharedEditorServer.dir/ServerThread.cpp.obj: ../ServerThread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\poliTO\magistrale\Programmazione di Sistema\Malnati\laboratori\progetto\SharedEditorServer\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/SharedEditorServer.dir/ServerThread.cpp.obj"
	D:\PROGRA~2\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\SharedEditorServer.dir\ServerThread.cpp.obj -c "D:\poliTO\magistrale\Programmazione di Sistema\Malnati\laboratori\progetto\SharedEditorServer\ServerThread.cpp"

CMakeFiles/SharedEditorServer.dir/ServerThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SharedEditorServer.dir/ServerThread.cpp.i"
	D:\PROGRA~2\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\poliTO\magistrale\Programmazione di Sistema\Malnati\laboratori\progetto\SharedEditorServer\ServerThread.cpp" > CMakeFiles\SharedEditorServer.dir\ServerThread.cpp.i

CMakeFiles/SharedEditorServer.dir/ServerThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SharedEditorServer.dir/ServerThread.cpp.s"
	D:\PROGRA~2\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\poliTO\magistrale\Programmazione di Sistema\Malnati\laboratori\progetto\SharedEditorServer\ServerThread.cpp" -o CMakeFiles\SharedEditorServer.dir\ServerThread.cpp.s

# Object files for target SharedEditorServer
SharedEditorServer_OBJECTS = \
"CMakeFiles/SharedEditorServer.dir/SharedEditorServer_autogen/mocs_compilation.cpp.obj" \
"CMakeFiles/SharedEditorServer.dir/main.cpp.obj" \
"CMakeFiles/SharedEditorServer.dir/NetworkServer.cpp.obj" \
"CMakeFiles/SharedEditorServer.dir/Symbol.cpp.obj" \
"CMakeFiles/SharedEditorServer.dir/SymId.cpp.obj" \
"CMakeFiles/SharedEditorServer.dir/Message.cpp.obj" \
"CMakeFiles/SharedEditorServer.dir/ServerThread.cpp.obj"

# External object files for target SharedEditorServer
SharedEditorServer_EXTERNAL_OBJECTS =

SharedEditorServer.exe: CMakeFiles/SharedEditorServer.dir/SharedEditorServer_autogen/mocs_compilation.cpp.obj
SharedEditorServer.exe: CMakeFiles/SharedEditorServer.dir/main.cpp.obj
SharedEditorServer.exe: CMakeFiles/SharedEditorServer.dir/NetworkServer.cpp.obj
SharedEditorServer.exe: CMakeFiles/SharedEditorServer.dir/Symbol.cpp.obj
SharedEditorServer.exe: CMakeFiles/SharedEditorServer.dir/SymId.cpp.obj
SharedEditorServer.exe: CMakeFiles/SharedEditorServer.dir/Message.cpp.obj
SharedEditorServer.exe: CMakeFiles/SharedEditorServer.dir/ServerThread.cpp.obj
SharedEditorServer.exe: CMakeFiles/SharedEditorServer.dir/build.make
SharedEditorServer.exe: C:/Qt/5.12.5/mingw73_64/lib/libQt5Chartsd.a
SharedEditorServer.exe: C:/Qt/5.12.5/mingw73_64/lib/libQt5Networkd.a
SharedEditorServer.exe: C:/Qt/5.12.5/mingw73_64/lib/libQt5Widgetsd.a
SharedEditorServer.exe: C:/Qt/5.12.5/mingw73_64/lib/libQt5Guid.a
SharedEditorServer.exe: C:/Qt/5.12.5/mingw73_64/lib/libQt5Cored.a
SharedEditorServer.exe: CMakeFiles/SharedEditorServer.dir/linklibs.rsp
SharedEditorServer.exe: CMakeFiles/SharedEditorServer.dir/objects1.rsp
SharedEditorServer.exe: CMakeFiles/SharedEditorServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="D:\poliTO\magistrale\Programmazione di Sistema\Malnati\laboratori\progetto\SharedEditorServer\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable SharedEditorServer.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\SharedEditorServer.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SharedEditorServer.dir/build: SharedEditorServer.exe

.PHONY : CMakeFiles/SharedEditorServer.dir/build

CMakeFiles/SharedEditorServer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\SharedEditorServer.dir\cmake_clean.cmake
.PHONY : CMakeFiles/SharedEditorServer.dir/clean

CMakeFiles/SharedEditorServer.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "D:\poliTO\magistrale\Programmazione di Sistema\Malnati\laboratori\progetto\SharedEditorServer" "D:\poliTO\magistrale\Programmazione di Sistema\Malnati\laboratori\progetto\SharedEditorServer" "D:\poliTO\magistrale\Programmazione di Sistema\Malnati\laboratori\progetto\SharedEditorServer\cmake-build-debug" "D:\poliTO\magistrale\Programmazione di Sistema\Malnati\laboratori\progetto\SharedEditorServer\cmake-build-debug" "D:\poliTO\magistrale\Programmazione di Sistema\Malnati\laboratori\progetto\SharedEditorServer\cmake-build-debug\CMakeFiles\SharedEditorServer.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/SharedEditorServer.dir/depend

