# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/abanwait/Downloads/rapidjson-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/abanwait/CLionProjects/Brand-New-Computer-Vision-Repo.-2020---2021-

# Include any dependencies generated for this target.
include example/CMakeFiles/tutorial.dir/depend.make

# Include the progress variables for this target.
include example/CMakeFiles/tutorial.dir/progress.make

# Include the compile flags for this target's objects.
include example/CMakeFiles/tutorial.dir/flags.make

example/CMakeFiles/tutorial.dir/tutorial/tutorial.cpp.o: example/CMakeFiles/tutorial.dir/flags.make
example/CMakeFiles/tutorial.dir/tutorial/tutorial.cpp.o: /home/abanwait/Downloads/rapidjson-master/example/tutorial/tutorial.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/abanwait/CLionProjects/Brand-New-Computer-Vision-Repo.-2020---2021-/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object example/CMakeFiles/tutorial.dir/tutorial/tutorial.cpp.o"
	cd /home/abanwait/CLionProjects/Brand-New-Computer-Vision-Repo.-2020---2021-/example && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tutorial.dir/tutorial/tutorial.cpp.o -c /home/abanwait/Downloads/rapidjson-master/example/tutorial/tutorial.cpp

example/CMakeFiles/tutorial.dir/tutorial/tutorial.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tutorial.dir/tutorial/tutorial.cpp.i"
	cd /home/abanwait/CLionProjects/Brand-New-Computer-Vision-Repo.-2020---2021-/example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/abanwait/Downloads/rapidjson-master/example/tutorial/tutorial.cpp > CMakeFiles/tutorial.dir/tutorial/tutorial.cpp.i

example/CMakeFiles/tutorial.dir/tutorial/tutorial.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tutorial.dir/tutorial/tutorial.cpp.s"
	cd /home/abanwait/CLionProjects/Brand-New-Computer-Vision-Repo.-2020---2021-/example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/abanwait/Downloads/rapidjson-master/example/tutorial/tutorial.cpp -o CMakeFiles/tutorial.dir/tutorial/tutorial.cpp.s

example/CMakeFiles/tutorial.dir/tutorial/tutorial.cpp.o.requires:

.PHONY : example/CMakeFiles/tutorial.dir/tutorial/tutorial.cpp.o.requires

example/CMakeFiles/tutorial.dir/tutorial/tutorial.cpp.o.provides: example/CMakeFiles/tutorial.dir/tutorial/tutorial.cpp.o.requires
	$(MAKE) -f example/CMakeFiles/tutorial.dir/build.make example/CMakeFiles/tutorial.dir/tutorial/tutorial.cpp.o.provides.build
.PHONY : example/CMakeFiles/tutorial.dir/tutorial/tutorial.cpp.o.provides

example/CMakeFiles/tutorial.dir/tutorial/tutorial.cpp.o.provides.build: example/CMakeFiles/tutorial.dir/tutorial/tutorial.cpp.o


# Object files for target tutorial
tutorial_OBJECTS = \
"CMakeFiles/tutorial.dir/tutorial/tutorial.cpp.o"

# External object files for target tutorial
tutorial_EXTERNAL_OBJECTS =

bin/tutorial: example/CMakeFiles/tutorial.dir/tutorial/tutorial.cpp.o
bin/tutorial: example/CMakeFiles/tutorial.dir/build.make
bin/tutorial: example/CMakeFiles/tutorial.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/abanwait/CLionProjects/Brand-New-Computer-Vision-Repo.-2020---2021-/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/tutorial"
	cd /home/abanwait/CLionProjects/Brand-New-Computer-Vision-Repo.-2020---2021-/example && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tutorial.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
example/CMakeFiles/tutorial.dir/build: bin/tutorial

.PHONY : example/CMakeFiles/tutorial.dir/build

example/CMakeFiles/tutorial.dir/requires: example/CMakeFiles/tutorial.dir/tutorial/tutorial.cpp.o.requires

.PHONY : example/CMakeFiles/tutorial.dir/requires

example/CMakeFiles/tutorial.dir/clean:
	cd /home/abanwait/CLionProjects/Brand-New-Computer-Vision-Repo.-2020---2021-/example && $(CMAKE_COMMAND) -P CMakeFiles/tutorial.dir/cmake_clean.cmake
.PHONY : example/CMakeFiles/tutorial.dir/clean

example/CMakeFiles/tutorial.dir/depend:
	cd /home/abanwait/CLionProjects/Brand-New-Computer-Vision-Repo.-2020---2021- && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/abanwait/Downloads/rapidjson-master /home/abanwait/Downloads/rapidjson-master/example /home/abanwait/CLionProjects/Brand-New-Computer-Vision-Repo.-2020---2021- /home/abanwait/CLionProjects/Brand-New-Computer-Vision-Repo.-2020---2021-/example /home/abanwait/CLionProjects/Brand-New-Computer-Vision-Repo.-2020---2021-/example/CMakeFiles/tutorial.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : example/CMakeFiles/tutorial.dir/depend

