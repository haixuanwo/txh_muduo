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
include CMakeFiles/discard.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/discard.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/discard.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/discard.dir/flags.make

CMakeFiles/discard.dir/examples/01_simple/02_discard/discard.cc.o: CMakeFiles/discard.dir/flags.make
CMakeFiles/discard.dir/examples/01_simple/02_discard/discard.cc.o: ../examples/01_simple/02_discard/discard.cc
CMakeFiles/discard.dir/examples/01_simple/02_discard/discard.cc.o: CMakeFiles/discard.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/txh/05_github/muduo/txh_muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/discard.dir/examples/01_simple/02_discard/discard.cc.o"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/discard.dir/examples/01_simple/02_discard/discard.cc.o -MF CMakeFiles/discard.dir/examples/01_simple/02_discard/discard.cc.o.d -o CMakeFiles/discard.dir/examples/01_simple/02_discard/discard.cc.o -c /home/txh/05_github/muduo/txh_muduo/examples/01_simple/02_discard/discard.cc

CMakeFiles/discard.dir/examples/01_simple/02_discard/discard.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/discard.dir/examples/01_simple/02_discard/discard.cc.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/txh/05_github/muduo/txh_muduo/examples/01_simple/02_discard/discard.cc > CMakeFiles/discard.dir/examples/01_simple/02_discard/discard.cc.i

CMakeFiles/discard.dir/examples/01_simple/02_discard/discard.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/discard.dir/examples/01_simple/02_discard/discard.cc.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/txh/05_github/muduo/txh_muduo/examples/01_simple/02_discard/discard.cc -o CMakeFiles/discard.dir/examples/01_simple/02_discard/discard.cc.s

CMakeFiles/discard.dir/examples/01_simple/02_discard/main.cc.o: CMakeFiles/discard.dir/flags.make
CMakeFiles/discard.dir/examples/01_simple/02_discard/main.cc.o: ../examples/01_simple/02_discard/main.cc
CMakeFiles/discard.dir/examples/01_simple/02_discard/main.cc.o: CMakeFiles/discard.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/txh/05_github/muduo/txh_muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/discard.dir/examples/01_simple/02_discard/main.cc.o"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/discard.dir/examples/01_simple/02_discard/main.cc.o -MF CMakeFiles/discard.dir/examples/01_simple/02_discard/main.cc.o.d -o CMakeFiles/discard.dir/examples/01_simple/02_discard/main.cc.o -c /home/txh/05_github/muduo/txh_muduo/examples/01_simple/02_discard/main.cc

CMakeFiles/discard.dir/examples/01_simple/02_discard/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/discard.dir/examples/01_simple/02_discard/main.cc.i"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/txh/05_github/muduo/txh_muduo/examples/01_simple/02_discard/main.cc > CMakeFiles/discard.dir/examples/01_simple/02_discard/main.cc.i

CMakeFiles/discard.dir/examples/01_simple/02_discard/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/discard.dir/examples/01_simple/02_discard/main.cc.s"
	g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/txh/05_github/muduo/txh_muduo/examples/01_simple/02_discard/main.cc -o CMakeFiles/discard.dir/examples/01_simple/02_discard/main.cc.s

# Object files for target discard
discard_OBJECTS = \
"CMakeFiles/discard.dir/examples/01_simple/02_discard/discard.cc.o" \
"CMakeFiles/discard.dir/examples/01_simple/02_discard/main.cc.o"

# External object files for target discard
discard_EXTERNAL_OBJECTS =

bin/discard: CMakeFiles/discard.dir/examples/01_simple/02_discard/discard.cc.o
bin/discard: CMakeFiles/discard.dir/examples/01_simple/02_discard/main.cc.o
bin/discard: CMakeFiles/discard.dir/build.make
bin/discard: ../lib/libmuduo_net.a
bin/discard: ../lib/libmuduo_base.a
bin/discard: CMakeFiles/discard.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/txh/05_github/muduo/txh_muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable bin/discard"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/discard.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/discard.dir/build: bin/discard
.PHONY : CMakeFiles/discard.dir/build

CMakeFiles/discard.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/discard.dir/cmake_clean.cmake
.PHONY : CMakeFiles/discard.dir/clean

CMakeFiles/discard.dir/depend:
	cd /home/txh/05_github/muduo/txh_muduo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/txh/05_github/muduo/txh_muduo /home/txh/05_github/muduo/txh_muduo /home/txh/05_github/muduo/txh_muduo/build /home/txh/05_github/muduo/txh_muduo/build /home/txh/05_github/muduo/txh_muduo/build/CMakeFiles/discard.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/discard.dir/depend
