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
include example/CMakeFiles/serialize.dir/depend.make

# Include the progress variables for this target.
include example/CMakeFiles/serialize.dir/progress.make

# Include the compile flags for this target's objects.
include example/CMakeFiles/serialize.dir/flags.make

example/CMakeFiles/serialize.dir/serialize/serialize.cpp.o: example/CMakeFiles/serialize.dir/flags.make
example/CMakeFiles/serialize.dir/serialize/serialize.cpp.o: /home/abanwait/Downloads/rapidjson-master/example/serialize/serialize.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/abanwait/CLionProjects/Brand-New-Computer-Vision-Repo.-2020---2021-/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object example/CMakeFiles/serialize.dir/serialize/serialize.cpp.o"
	cd /home/abanwait/CLionProjects/Brand-New-Computer-Vision-Repo.-2020---2021-/example && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/serialize.dir/serialize/serialize.cpp.o -c /home/abanwait/Downloads/rapidjson-master/example/serialize/serialize.cpp

example/CMakeFiles/serialize.dir/serialize/serialize.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/serialize.dir/serialize/serialize.cpp.i"
	cd /home/abanwait/CLionProjects/Brand-New-Computer-Vision-Repo.-2020---2021-/example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/abanwait/Downloads/rapidjson-master/example/serialize/serialize.cpp > CMakeFiles/serialize.dir/serialize/serialize.cpp.i

example/CMakeFiles/serialize.dir/serialize/serialize.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/serialize.dir/serialize/serialize.cpp.s"
	cd /home/abanwait/CLionProjects/Brand-New-Computer-Vision-Repo.-2020---2021-/example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/abanwait/Downloads/rapidjson-master/example/serialize/serialize.cpp -o CMakeFiles/serialize.dir/serialize/serialize.cpp.s

example/CMakeFiles/serialize.dir/serialize/serialize.cpp.o.requires:

.PHONY : example/CMakeFiles/serialize.dir/serialize/serialize.cpp.o.requires

example/CMakeFiles/serialize.dir/serialize/serialize.cpp.o.provides: example/CMakeFiles/serialize.dir/serialize/serialize.cpp.o.requires
	$(MAKE) -f example/CMakeFiles/serialize.dir/build.make example/CMakeFiles/serialize.dir/serialize/serialize.cpp.o.provides.build
.PHONY : example/CMakeFiles/serialize.dir/serialize/serialize.cpp.o.provides

example/CMakeFiles/serialize.dir/serialize/serialize.cpp.o.provides.build: example/CMakeFiles/serialize.dir/serialize/serialize.cpp.o


# Object files for target serialize
serialize_OBJECTS = \
"CMakeFiles/serialize.dir/serialize/serialize.cpp.o"

# External object files for target serialize
serialize_EXTERNAL_OBJECTS =

bin/serialize: example/CMakeFiles/serialize.dir/serialize/serialize.cpp.o
bin/serialize: example/CMakeFiles/serialize.dir/build.make
bin/serialize: example/CMakeFiles/serialize.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/abanwait/CLionProjects/Brand-New-Computer-Vision-Repo.-2020---2021-/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/serialize"
	cd /home/abanwait/CLionProjects/Brand-New-Computer-Vision-Repo.-2020---2021-/example && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/serialize.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
example/CMakeFiles/serialize.dir/build: bin/serialize

.PHONY : example/CMakeFiles/serialize.dir/build

example/CMakeFiles/serialize.dir/requires: example/CMakeFiles/serialize.dir/serialize/serialize.cpp.o.requires

.PHONY : example/CMakeFiles/serialize.dir/requires

example/CMakeFiles/serialize.dir/clean:
	cd /home/abanwait/CLionProjects/Brand-New-Computer-Vision-Repo.-2020---2021-/example && $(CMAKE_COMMAND) -P CMakeFiles/serialize.dir/cmake_clean.cmake
.PHONY : example/CMakeFiles/serialize.dir/clean

example/CMakeFiles/serialize.dir/depend:
	cd /home/abanwait/CLionProjects/Brand-New-Computer-Vision-Repo.-2020---2021- && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/abanwait/Downloads/rapidjson-master /home/abanwait/Downloads/rapidjson-master/example /home/abanwait/CLionProjects/Brand-New-Computer-Vision-Repo.-2020---2021- /home/abanwait/CLionProjects/Brand-New-Computer-Vision-Repo.-2020---2021-/example /home/abanwait/CLionProjects/Brand-New-Computer-Vision-Repo.-2020---2021-/example/CMakeFiles/serialize.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : example/CMakeFiles/serialize.dir/depend

