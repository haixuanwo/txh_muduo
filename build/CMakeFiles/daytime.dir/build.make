# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/txh/05_github/muduo/txh_muduo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/txh/05_github/muduo/txh_muduo/build

# Include any dependencies generated for this target.
include CMakeFiles/daytime.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/daytime.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/daytime.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/daytime.dir/flags.make

CMakeFiles/daytime.dir/examples/01_simple/05_daytime/daytime.cc.o: CMakeFiles/daytime.dir/flags.make
CMakeFiles/daytime.dir/examples/01_simple/05_daytime/daytime.cc.o: ../examples/01_simple/05_daytime/daytime.cc
CMakeFiles/daytime.dir/examples/01_simple/05_daytime/daytime.cc.o: CMakeFiles/daytime.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/txh/05_github/muduo/txh_muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/daytime.dir/examples/01_simple/05_daytime/daytime.cc.o"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/daytime.dir/examples/01_simple/05_daytime/daytime.cc.o -MF CMakeFiles/daytime.dir/examples/01_simple/05_daytime/daytime.cc.o.d -o CMakeFiles/daytime.dir/examples/01_simple/05_daytime/daytime.cc.o -c /home/txh/05_github/muduo/txh_muduo/examples/01_simple/05_daytime/daytime.cc

CMakeFiles/daytime.dir/examples/01_simple/05_daytime/daytime.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/daytime.dir/examples/01_simple/05_daytime/daytime.cc.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/txh/05_github/muduo/txh_muduo/examples/01_simple/05_daytime/daytime.cc > CMakeFiles/daytime.dir/examples/01_simple/05_daytime/daytime.cc.i

CMakeFiles/daytime.dir/examples/01_simple/05_daytime/daytime.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/daytime.dir/examples/01_simple/05_daytime/daytime.cc.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/txh/05_github/muduo/txh_muduo/examples/01_simple/05_daytime/daytime.cc -o CMakeFiles/daytime.dir/examples/01_simple/05_daytime/daytime.cc.s

CMakeFiles/daytime.dir/examples/01_simple/05_daytime/main.cc.o: CMakeFiles/daytime.dir/flags.make
CMakeFiles/daytime.dir/examples/01_simple/05_daytime/main.cc.o: ../examples/01_simple/05_daytime/main.cc
CMakeFiles/daytime.dir/examples/01_simple/05_daytime/main.cc.o: CMakeFiles/daytime.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/txh/05_github/muduo/txh_muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/daytime.dir/examples/01_simple/05_daytime/main.cc.o"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/daytime.dir/examples/01_simple/05_daytime/main.cc.o -MF CMakeFiles/daytime.dir/examples/01_simple/05_daytime/main.cc.o.d -o CMakeFiles/daytime.dir/examples/01_simple/05_daytime/main.cc.o -c /home/txh/05_github/muduo/txh_muduo/examples/01_simple/05_daytime/main.cc

CMakeFiles/daytime.dir/examples/01_simple/05_daytime/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/daytime.dir/examples/01_simple/05_daytime/main.cc.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/txh/05_github/muduo/txh_muduo/examples/01_simple/05_daytime/main.cc > CMakeFiles/daytime.dir/examples/01_simple/05_daytime/main.cc.i

CMakeFiles/daytime.dir/examples/01_simple/05_daytime/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/daytime.dir/examples/01_simple/05_daytime/main.cc.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/txh/05_github/muduo/txh_muduo/examples/01_simple/05_daytime/main.cc -o CMakeFiles/daytime.dir/examples/01_simple/05_daytime/main.cc.s

# Object files for target daytime
daytime_OBJECTS = \
"CMakeFiles/daytime.dir/examples/01_simple/05_daytime/daytime.cc.o" \
"CMakeFiles/daytime.dir/examples/01_simple/05_daytime/main.cc.o"

# External object files for target daytime
daytime_EXTERNAL_OBJECTS =

bin/daytime: CMakeFiles/daytime.dir/examples/01_simple/05_daytime/daytime.cc.o
bin/daytime: CMakeFiles/daytime.dir/examples/01_simple/05_daytime/main.cc.o
bin/daytime: CMakeFiles/daytime.dir/build.make
bin/daytime: ../lib/libmuduo_net.a
bin/daytime: ../lib/libmuduo_base.a
bin/daytime: CMakeFiles/daytime.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/txh/05_github/muduo/txh_muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable bin/daytime"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/daytime.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/daytime.dir/build: bin/daytime
.PHONY : CMakeFiles/daytime.dir/build

CMakeFiles/daytime.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/daytime.dir/cmake_clean.cmake
.PHONY : CMakeFiles/daytime.dir/clean

CMakeFiles/daytime.dir/depend:
	cd /home/txh/05_github/muduo/txh_muduo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/txh/05_github/muduo/txh_muduo /home/txh/05_github/muduo/txh_muduo /home/txh/05_github/muduo/txh_muduo/build /home/txh/05_github/muduo/txh_muduo/build /home/txh/05_github/muduo/txh_muduo/build/CMakeFiles/daytime.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/daytime.dir/depend

