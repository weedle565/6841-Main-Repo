# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.29

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "F:\CLION\CLion 2024.2.1\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "F:\CLION\CLion 2024.2.1\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\olive\CLionProjects\6841-Project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\olive\CLionProjects\6841-Project\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/6841Project.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/6841Project.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/6841Project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/6841Project.dir/flags.make

CMakeFiles/6841Project.dir/server/server.c.obj: CMakeFiles/6841Project.dir/flags.make
CMakeFiles/6841Project.dir/server/server.c.obj: CMakeFiles/6841Project.dir/includes_C.rsp
CMakeFiles/6841Project.dir/server/server.c.obj: C:/Users/olive/CLionProjects/6841-Project/server/server.c
CMakeFiles/6841Project.dir/server/server.c.obj: CMakeFiles/6841Project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\olive\CLionProjects\6841-Project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/6841Project.dir/server/server.c.obj"
	"F:\CLION\CLion 2024.2.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/6841Project.dir/server/server.c.obj -MF CMakeFiles\6841Project.dir\server\server.c.obj.d -o CMakeFiles\6841Project.dir\server\server.c.obj -c C:\Users\olive\CLionProjects\6841-Project\server\server.c

CMakeFiles/6841Project.dir/server/server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/6841Project.dir/server/server.c.i"
	"F:\CLION\CLion 2024.2.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\olive\CLionProjects\6841-Project\server\server.c > CMakeFiles\6841Project.dir\server\server.c.i

CMakeFiles/6841Project.dir/server/server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/6841Project.dir/server/server.c.s"
	"F:\CLION\CLion 2024.2.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\olive\CLionProjects\6841-Project\server\server.c -o CMakeFiles\6841Project.dir\server\server.c.s

CMakeFiles/6841Project.dir/server/microui.c.obj: CMakeFiles/6841Project.dir/flags.make
CMakeFiles/6841Project.dir/server/microui.c.obj: CMakeFiles/6841Project.dir/includes_C.rsp
CMakeFiles/6841Project.dir/server/microui.c.obj: C:/Users/olive/CLionProjects/6841-Project/server/microui.c
CMakeFiles/6841Project.dir/server/microui.c.obj: CMakeFiles/6841Project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\olive\CLionProjects\6841-Project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/6841Project.dir/server/microui.c.obj"
	"F:\CLION\CLion 2024.2.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/6841Project.dir/server/microui.c.obj -MF CMakeFiles\6841Project.dir\server\microui.c.obj.d -o CMakeFiles\6841Project.dir\server\microui.c.obj -c C:\Users\olive\CLionProjects\6841-Project\server\microui.c

CMakeFiles/6841Project.dir/server/microui.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/6841Project.dir/server/microui.c.i"
	"F:\CLION\CLion 2024.2.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\olive\CLionProjects\6841-Project\server\microui.c > CMakeFiles\6841Project.dir\server\microui.c.i

CMakeFiles/6841Project.dir/server/microui.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/6841Project.dir/server/microui.c.s"
	"F:\CLION\CLion 2024.2.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\olive\CLionProjects\6841-Project\server\microui.c -o CMakeFiles\6841Project.dir\server\microui.c.s

CMakeFiles/6841Project.dir/server_window.c.obj: CMakeFiles/6841Project.dir/flags.make
CMakeFiles/6841Project.dir/server_window.c.obj: CMakeFiles/6841Project.dir/includes_C.rsp
CMakeFiles/6841Project.dir/server_window.c.obj: C:/Users/olive/CLionProjects/6841-Project/server_window.c
CMakeFiles/6841Project.dir/server_window.c.obj: CMakeFiles/6841Project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\olive\CLionProjects\6841-Project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/6841Project.dir/server_window.c.obj"
	"F:\CLION\CLion 2024.2.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/6841Project.dir/server_window.c.obj -MF CMakeFiles\6841Project.dir\server_window.c.obj.d -o CMakeFiles\6841Project.dir\server_window.c.obj -c C:\Users\olive\CLionProjects\6841-Project\server_window.c

CMakeFiles/6841Project.dir/server_window.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/6841Project.dir/server_window.c.i"
	"F:\CLION\CLion 2024.2.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\olive\CLionProjects\6841-Project\server_window.c > CMakeFiles\6841Project.dir\server_window.c.i

CMakeFiles/6841Project.dir/server_window.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/6841Project.dir/server_window.c.s"
	"F:\CLION\CLion 2024.2.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\olive\CLionProjects\6841-Project\server_window.c -o CMakeFiles\6841Project.dir\server_window.c.s

CMakeFiles/6841Project.dir/server/render.c.obj: CMakeFiles/6841Project.dir/flags.make
CMakeFiles/6841Project.dir/server/render.c.obj: CMakeFiles/6841Project.dir/includes_C.rsp
CMakeFiles/6841Project.dir/server/render.c.obj: C:/Users/olive/CLionProjects/6841-Project/server/render.c
CMakeFiles/6841Project.dir/server/render.c.obj: CMakeFiles/6841Project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\olive\CLionProjects\6841-Project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/6841Project.dir/server/render.c.obj"
	"F:\CLION\CLion 2024.2.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/6841Project.dir/server/render.c.obj -MF CMakeFiles\6841Project.dir\server\render.c.obj.d -o CMakeFiles\6841Project.dir\server\render.c.obj -c C:\Users\olive\CLionProjects\6841-Project\server\render.c

CMakeFiles/6841Project.dir/server/render.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/6841Project.dir/server/render.c.i"
	"F:\CLION\CLion 2024.2.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\olive\CLionProjects\6841-Project\server\render.c > CMakeFiles\6841Project.dir\server\render.c.i

CMakeFiles/6841Project.dir/server/render.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/6841Project.dir/server/render.c.s"
	"F:\CLION\CLion 2024.2.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\olive\CLionProjects\6841-Project\server\render.c -o CMakeFiles\6841Project.dir\server\render.c.s

CMakeFiles/6841Project.dir/functions/keylogger.c.obj: CMakeFiles/6841Project.dir/flags.make
CMakeFiles/6841Project.dir/functions/keylogger.c.obj: CMakeFiles/6841Project.dir/includes_C.rsp
CMakeFiles/6841Project.dir/functions/keylogger.c.obj: C:/Users/olive/CLionProjects/6841-Project/functions/keylogger.c
CMakeFiles/6841Project.dir/functions/keylogger.c.obj: CMakeFiles/6841Project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\olive\CLionProjects\6841-Project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/6841Project.dir/functions/keylogger.c.obj"
	"F:\CLION\CLion 2024.2.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/6841Project.dir/functions/keylogger.c.obj -MF CMakeFiles\6841Project.dir\functions\keylogger.c.obj.d -o CMakeFiles\6841Project.dir\functions\keylogger.c.obj -c C:\Users\olive\CLionProjects\6841-Project\functions\keylogger.c

CMakeFiles/6841Project.dir/functions/keylogger.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/6841Project.dir/functions/keylogger.c.i"
	"F:\CLION\CLion 2024.2.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\olive\CLionProjects\6841-Project\functions\keylogger.c > CMakeFiles\6841Project.dir\functions\keylogger.c.i

CMakeFiles/6841Project.dir/functions/keylogger.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/6841Project.dir/functions/keylogger.c.s"
	"F:\CLION\CLion 2024.2.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\olive\CLionProjects\6841-Project\functions\keylogger.c -o CMakeFiles\6841Project.dir\functions\keylogger.c.s

# Object files for target 6841Project
6841Project_OBJECTS = \
"CMakeFiles/6841Project.dir/server/server.c.obj" \
"CMakeFiles/6841Project.dir/server/microui.c.obj" \
"CMakeFiles/6841Project.dir/server_window.c.obj" \
"CMakeFiles/6841Project.dir/server/render.c.obj" \
"CMakeFiles/6841Project.dir/functions/keylogger.c.obj"

# External object files for target 6841Project
6841Project_EXTERNAL_OBJECTS =

6841Project.exe: CMakeFiles/6841Project.dir/server/server.c.obj
6841Project.exe: CMakeFiles/6841Project.dir/server/microui.c.obj
6841Project.exe: CMakeFiles/6841Project.dir/server_window.c.obj
6841Project.exe: CMakeFiles/6841Project.dir/server/render.c.obj
6841Project.exe: CMakeFiles/6841Project.dir/functions/keylogger.c.obj
6841Project.exe: CMakeFiles/6841Project.dir/build.make
6841Project.exe: CMakeFiles/6841Project.dir/linkLibs.rsp
6841Project.exe: CMakeFiles/6841Project.dir/objects1.rsp
6841Project.exe: CMakeFiles/6841Project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\olive\CLionProjects\6841-Project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable 6841Project.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\6841Project.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/6841Project.dir/build: 6841Project.exe
.PHONY : CMakeFiles/6841Project.dir/build

CMakeFiles/6841Project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\6841Project.dir\cmake_clean.cmake
.PHONY : CMakeFiles/6841Project.dir/clean

CMakeFiles/6841Project.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\olive\CLionProjects\6841-Project C:\Users\olive\CLionProjects\6841-Project C:\Users\olive\CLionProjects\6841-Project\cmake-build-debug C:\Users\olive\CLionProjects\6841-Project\cmake-build-debug C:\Users\olive\CLionProjects\6841-Project\cmake-build-debug\CMakeFiles\6841Project.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/6841Project.dir/depend

