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
include CMakeFiles/client.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/client.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/client.dir/flags.make

CMakeFiles/client.dir/client/system.c.obj: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/client/system.c.obj: CMakeFiles/client.dir/includes_C.rsp
CMakeFiles/client.dir/client/system.c.obj: C:/Users/olive/CLionProjects/6841-Project/client/system.c
CMakeFiles/client.dir/client/system.c.obj: CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\olive\CLionProjects\6841-Project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/client.dir/client/system.c.obj"
	"F:\CLION\CLion 2024.2.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/client.dir/client/system.c.obj -MF CMakeFiles\client.dir\client\system.c.obj.d -o CMakeFiles\client.dir\client\system.c.obj -c C:\Users\olive\CLionProjects\6841-Project\client\system.c

CMakeFiles/client.dir/client/system.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/client.dir/client/system.c.i"
	"F:\CLION\CLion 2024.2.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\olive\CLionProjects\6841-Project\client\system.c > CMakeFiles\client.dir\client\system.c.i

CMakeFiles/client.dir/client/system.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/client.dir/client/system.c.s"
	"F:\CLION\CLion 2024.2.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\olive\CLionProjects\6841-Project\client\system.c -o CMakeFiles\client.dir\client\system.c.s

CMakeFiles/client.dir/functions/keylogger.c.obj: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/functions/keylogger.c.obj: CMakeFiles/client.dir/includes_C.rsp
CMakeFiles/client.dir/functions/keylogger.c.obj: C:/Users/olive/CLionProjects/6841-Project/functions/keylogger.c
CMakeFiles/client.dir/functions/keylogger.c.obj: CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\olive\CLionProjects\6841-Project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/client.dir/functions/keylogger.c.obj"
	"F:\CLION\CLion 2024.2.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/client.dir/functions/keylogger.c.obj -MF CMakeFiles\client.dir\functions\keylogger.c.obj.d -o CMakeFiles\client.dir\functions\keylogger.c.obj -c C:\Users\olive\CLionProjects\6841-Project\functions\keylogger.c

CMakeFiles/client.dir/functions/keylogger.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/client.dir/functions/keylogger.c.i"
	"F:\CLION\CLion 2024.2.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\olive\CLionProjects\6841-Project\functions\keylogger.c > CMakeFiles\client.dir\functions\keylogger.c.i

CMakeFiles/client.dir/functions/keylogger.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/client.dir/functions/keylogger.c.s"
	"F:\CLION\CLion 2024.2.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\olive\CLionProjects\6841-Project\functions\keylogger.c -o CMakeFiles\client.dir\functions\keylogger.c.s

CMakeFiles/client.dir/client/trojan.c.obj: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/client/trojan.c.obj: CMakeFiles/client.dir/includes_C.rsp
CMakeFiles/client.dir/client/trojan.c.obj: C:/Users/olive/CLionProjects/6841-Project/client/trojan.c
CMakeFiles/client.dir/client/trojan.c.obj: CMakeFiles/client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\olive\CLionProjects\6841-Project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/client.dir/client/trojan.c.obj"
	"F:\CLION\CLion 2024.2.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/client.dir/client/trojan.c.obj -MF CMakeFiles\client.dir\client\trojan.c.obj.d -o CMakeFiles\client.dir\client\trojan.c.obj -c C:\Users\olive\CLionProjects\6841-Project\client\trojan.c

CMakeFiles/client.dir/client/trojan.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/client.dir/client/trojan.c.i"
	"F:\CLION\CLion 2024.2.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\olive\CLionProjects\6841-Project\client\trojan.c > CMakeFiles\client.dir\client\trojan.c.i

CMakeFiles/client.dir/client/trojan.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/client.dir/client/trojan.c.s"
	"F:\CLION\CLion 2024.2.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\olive\CLionProjects\6841-Project\client\trojan.c -o CMakeFiles\client.dir\client\trojan.c.s

# Object files for target client
client_OBJECTS = \
"CMakeFiles/client.dir/client/system.c.obj" \
"CMakeFiles/client.dir/functions/keylogger.c.obj" \
"CMakeFiles/client.dir/client/trojan.c.obj"

# External object files for target client
client_EXTERNAL_OBJECTS =

client.exe: CMakeFiles/client.dir/client/system.c.obj
client.exe: CMakeFiles/client.dir/functions/keylogger.c.obj
client.exe: CMakeFiles/client.dir/client/trojan.c.obj
client.exe: CMakeFiles/client.dir/build.make
client.exe: CMakeFiles/client.dir/linkLibs.rsp
client.exe: CMakeFiles/client.dir/objects1.rsp
client.exe: CMakeFiles/client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\olive\CLionProjects\6841-Project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable client.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\client.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/client.dir/build: client.exe
.PHONY : CMakeFiles/client.dir/build

CMakeFiles/client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\client.dir\cmake_clean.cmake
.PHONY : CMakeFiles/client.dir/clean

CMakeFiles/client.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\olive\CLionProjects\6841-Project C:\Users\olive\CLionProjects\6841-Project C:\Users\olive\CLionProjects\6841-Project\cmake-build-debug C:\Users\olive\CLionProjects\6841-Project\cmake-build-debug C:\Users\olive\CLionProjects\6841-Project\cmake-build-debug\CMakeFiles\client.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/client.dir/depend

